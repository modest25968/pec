#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTimer>
#include <QThread>

#define S_STOP 1
#define S_PLAY 2
#define S_PAUSE 3

class MSong;
class BackLoader;
class AbstractBackend;
class VolControll;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();
    QTimer* timer;
    QThread thread;
    MSong* song;
    BackLoader* bl;
    AbstractBackend* ab;
    VolControll* vc;
    bool isLooping;
    int status;
public slots:
    void startPlay();
    void stopPlay();
    void pausePlay();

    void songEnd();
    void setSong(MSong* song);
    int getSongDur();
    bool isBackLoad();

    void setEnabledCi(bool enabled);

signals:
    void updateScroll(int newTime, int newTimeS, int newTimeE);
    void forScrollNewSong(int dur);

    void changeVol(int chan,int vol);
    void newCountVoices(int count);

    void tick();
    void setTime(int time);
    void setStartCi();
    void setEndCi();
private:

};

#endif // PLAYER_H
