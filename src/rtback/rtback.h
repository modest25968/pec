#ifndef RTBACK_H
#define RTBACK_H

#include "rtback_global.h"

#include "../core/abstractbackend.h"

class RtMidiOut;

class Rtback: public AbstractBackend
{

public:
    Rtback();
    ~Rtback();
    void note_on(int chan, short key);
    void note_off(int chan, short key);
    void notes_off();

    void set_volume(int chan, int vol);
    void test();

    bool ready;
private:
    RtMidiOut *midiout;

};

extern "C" RTBACKSHARED_EXPORT AbstractBackend* getab()
{
    Rtback* rt = new Rtback();
    return rt;
}

#endif // RTBACK_H
