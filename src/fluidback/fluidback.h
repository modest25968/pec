#ifndef FLUIDBACK_H
#define FLUIDBACK_H

#include "fluidback_global.h"

#include "../core/abstractbackend.h"

#include "fluidsynth.h"
#include <QVector>

class  Fluidback : public AbstractBackend
{
public:
    Fluidback();
    void noteOn(int chan, short key);
    void noteOff(int chan, short key);
    void notesOff();

    void setVolume(int chan, int vol);
private:
    void createsynth();
    void loadsoundfont();
    void resetVolume(int newVolum);

    QVector<int> volumes;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    fluid_sequencer_t* sequencer;
    int synthSeqID;
};

extern "C" FLUIDBACKSHARED_EXPORT AbstractBackend* getab()
{
    Fluidback* flab = new Fluidback();
    return flab;

}

#endif // FLUIDBACK_H

