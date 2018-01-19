#ifndef MSONG_H
#define MSONG_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QMap>

#include "mnota.h"
#include "../core/xmlbasesong.h"

class AbstractBackend;

class MSong : public XmlBaseSong
{
    Q_OBJECT
public:
    explicit MSong(QObject *parent = 0);
    ~MSong();
    //MSong();
    void setPl(AbstractBackend* player);
    int getTempo();
    int getCountVoice();
    int getDur();
    QString getName();
    bool getLooping();
    void setTempo(int new_tempo);


    void createNextPart() {}
    void createEndPart() {}

    void createNextMissure(){}
    void createEndMissure();

    void createAddNota(Snote nota);
    void createAddAtr(Satr atr){
        Q_UNUSED(atr);
    }

    void setStart();
    void init();
public slots:
    void tick();
    void stopPlay();

    void setTime(int time);
    void setStartCi();
    void setEndCi();
    void setEnabledCi(bool enabled);
signals:
    void plNotaOn();
    void plNotaOff();
    void songEnd();
    void setSongForScroll(int dur);
    void updateScroll(int newTime, int newTimeS, int newTimeE);


private:
    QString name;
    QMap<int, int> map;
    //int tempo;
    int time;
    int timeStartCi;
    int timeEndCi;
    int dur;
    bool isLooping;
//    Player* pl;

    QVector<QVector<MNota*>> partNotes ;
    QVector<int> tekNotes;
    AbstractBackend* ab;
    void findNowNota(int time);
    void playTekNotes();

    void notaOn(MNota* nota, int channel);
    int notaOff(MNota* nota, int channel);

    void checkEndCi();
};

#endif // MSONG_H
