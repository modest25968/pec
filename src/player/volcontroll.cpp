#include "volcontroll.h"
#include "../core/abstractbackend.h"
VolControll::VolControll(QObject *parent) : QObject(parent)
{
    for (int i=0;i<16;i++)
        volums[i]=40;
    nv = 0;
}

void VolControll::setAb(AbstractBackend *ab)
{
    if (ab)
    {
        this->ab = ab;
        for (int i=0;i<nv;i++)
            ab->setVolume(i,volums[i]);
    }
}

void VolControll::setCountVoice(int cv)
{
    nv =  cv;
    emit countChange(cv);
}

void VolControll::setVolume(int chan, int vol)
{
    volums[chan] = vol;
    if (ab)
        ab->setVolume(chan, vol);
}
