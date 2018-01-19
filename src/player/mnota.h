#ifndef MNOTA_H
#define MNOTA_H

#include <QObject>
#include "../core/xmlbasesong.h"

/*
class BaseMusElem
{
public:
    virtual void play(int chan)=0;
    //virtual void stop(int chan)=0;
    virtual int getDur()=0;
    int time_start;
};*/

class MNota //: public BaseMusElem
{
public:
    MNota(int midi, int dur, bool next_in_chord, bool end_takt, bool isPause);
    MNota(Snote nota);
    int midi;
    int dur;
    bool next_in_chord;
    bool end_takt;
    bool isPause;
    MNota* next;

    int time_start;
    int getDur();
};

#endif // MNOTA_H
