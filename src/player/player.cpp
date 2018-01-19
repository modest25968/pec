#include "player.h"

#include "msong.h"
#include <QDebug>
#include "../backLoader/backloader.h"
#include "../core/abstractbackend.h"
#include "volcontroll.h"

Player::Player(QObject *parent)//: QObject(parent)
{
    Q_UNUSED(parent);
    isLooping = false;
    this->status = S_STOP;
    this->song = nullptr;
    thread.start();

    bl = new BackLoader();
    ab = bl->getBack();

    vc = new VolControll();
    vc->setAb(ab);
    connect(this, SIGNAL(changeVol(int,int)),
            vc, SLOT(setVolume(int,int)));
}

Player::~Player()
{
    timer->destroyed();
    thread.quit();
    thread.wait();
    thread.destroyed();
}

void Player::setSong(MSong* song)
{
    song->init();

    if (this->song!=nullptr)
    {
        this->stopPlay();
        //this->song->destroyed();
        this->song->destroyed();
        this->timer->destroyed();
    }
    song->setEnabledCi(isLooping);

    this->song = song;
    song->setPl(ab);

    vc->setCountVoice(song->getCountVoice());


    connect(song, SIGNAL(songEnd()),
            this, SLOT(songEnd()));

    //connect(this, SIGNAL(setEnabledCi(bool)),
    //        song, SLOT(setEnabledCi(bool)));

    connect(this, SIGNAL(setStartCi()),
            song, SLOT(setStartCi()));

    connect(this, SIGNAL(setEndCi()),
            song, SLOT(setEndCi()));

//    connect(this, SIGNAL(setEnabledCi(bool)),
//            song, SLOT(setEnabledCi(bool)));

    connect(this, SIGNAL(setTime(int)),
            song, SLOT(setTime(int)));

    emit forScrollNewSong(song->getDur());

    connect(song, SIGNAL(updateScroll(int,int,int)),
            this, SIGNAL(updateScroll(int,int,int)));



    timer  = new QTimer();
    timer->setInterval(15000 / song->getTempo());
    timer->start();
    timer->moveToThread(&thread);
    song->moveToThread(&thread);
    /*(this, SIGNAL(tick()),
            song, SLOT(tick()));*/


    emit newCountVoices(song->getCountVoice());
//    emit UpdateScroll();
}

int Player::getSongDur()
{
    if (song)
        return (song->getDur());
    else
        return -1;

}

bool Player::isBackLoad()
{
    return (!(ab==nullptr));
}

void Player::setEnabledCi(bool enabled)
{
    isLooping = enabled;
    if (song!=nullptr)
        song->setEnabledCi(isLooping);
}

void Player::startPlay()
{
    if (song != nullptr)
    {
        if (status == S_STOP)
        {
            connect(timer, SIGNAL(timeout()),
                    song, SLOT(tick()));
            status = S_PLAY;
        }
        else if (status == S_PAUSE)
        {
            connect(timer, SIGNAL(timeout()),
                    song, SLOT(tick()));
            status = S_PLAY;
        }
    }
}

void Player::stopPlay()
{
    if (song != nullptr)
    {
        if (status == S_PLAY)
        {
            disconnect(timer, SIGNAL(timeout()),
                       song, SLOT(tick()));
            song->stopPlay();
        }
        song->setStart();
        status = S_STOP;
    }
}

void Player::pausePlay()
{
    if (song != nullptr)
        if (status == S_PLAY)
        {
            disconnect(timer, SIGNAL(timeout()),
                       song, SLOT(tick()));
            status = S_PAUSE;
            song->stopPlay();
        }
}

void Player::songEnd()
{
    stopPlay();
}

