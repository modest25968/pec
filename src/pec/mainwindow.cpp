#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileSystemModel>

#include "../parser/parser.h"
#include "../player/player.h"

#include "../player/msong.h"
#include "../songSelector/songselector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ss = new SongSelector();
    QFileSystemModel* fsm = ss->getFSM();

    if (fsm == nullptr)
    {
        QCoreApplication::exit();
    }
    ui->treeView->setModel(fsm);
    //ui->treeView->setRootIndex(fsm->index(ss->getPath()));
    QHeaderView* head = ui->treeView->header();

    head->hideSection(1);
    head->hideSection(2);
    head->hideSection(3);

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
            ss, SLOT(selectTreeView(QModelIndex)));

    qDebug()<<"click";

    pl = new Player(this);

    playerConnect();
    buttonConnect();

    connect(ss, SIGNAL(msongSelect(MSong*)),
            pl, SLOT(setSong(MSong*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onPlayButtonClicked()
{
    pl->startPlay();
}

void MainWindow::onPauseButtonClicked()
{
    pl->pausePlay();
}

void MainWindow::onStopButtonClicked()
{
    pl->stopPlay();
}

void MainWindow::playerConnect()
{
    connect(pl, SIGNAL(tick()),
            ui->songScrollWidget, SLOT(tickEvent()));

    connect(pl, SIGNAL(updateScroll(int,int,int)),
            ui->songScrollWidget, SLOT(update(int,int,int)));

    connect(pl, SIGNAL(newCountVoices(int)),
            ui->volWidget, SLOT(setCount(int)));

    connect(ui->volWidget, SIGNAL(setVolume(int,int)),
            pl, SIGNAL(changeVol(int,int)));

    connect(ui->startCiBut, SIGNAL(clicked(bool)),
            pl, SIGNAL(setStartCi()));

    connect(ui->stopCiBut, SIGNAL(clicked(bool)),
            pl, SIGNAL(setEndCi()));

    connect(ui->enabledLoopBut, SIGNAL(toggled(bool)),
            pl, SLOT(setEnabledCi(bool)));

    connect(ui->songScrollWidget, SIGNAL(newTime(int)),
            pl, SIGNAL(setTime(int)));

    connect(pl, SIGNAL(forScrollNewSong(int)),
            ui->songScrollWidget, SLOT(songChange(int)));
}

void MainWindow::buttonConnect()
{
    connect(ui->playBut, SIGNAL(clicked(bool)),
            SLOT(onPlayButtonClicked()));
    connect(ui->stopBut, SIGNAL(clicked(bool)),
            SLOT(onStopButtonClicked()));
    connect(ui->pauseBut, SIGNAL(clicked(bool)),
            SLOT(onPauseButtonClicked()));
}
