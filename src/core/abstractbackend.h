#ifndef ABSTRACTBACKEND_H
#define ABSTRACTBACKEND_H

#include <QString>

class AbstractBackend
{
public:
    AbstractBackend(){};

    virtual void noteOn(int chan, short key)=0;
    virtual void noteOff(int chan, short key)=0;
    virtual void notesOff()=0;
    virtual void setVolume(int chan, int vol)=0;
    QString textError;
};

#endif // ABSTRACTBACKEND_H
