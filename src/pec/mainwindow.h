#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Player;
class SongSelector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void onPlayButtonClicked();

    void onPauseButtonClicked();

    void onStopButtonClicked();


private:
    Ui::MainWindow *ui;
    Player* pl;
    SongSelector* ss;
    void playerConnect();
    void buttonConnect();
};

#endif // MAINWINDOW_H
