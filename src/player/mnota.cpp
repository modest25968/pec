#include "mnota.h"
#include <QDebug>

MNota::MNota(int midi, int dur, bool next_in_chord, bool end_takt, bool isPause)
{
    this->midi = midi;
    this->dur = dur;
    this->next_in_chord = next_in_chord;
    this->end_takt = end_takt;
    this->isPause = isPause;
    next = nullptr;
}

MNota::MNota(Snote nota)
{
    this->midi = nota.midi;
    this->dur = nota.dur;
    this->next_in_chord = nota.in_chord;
    this->end_takt = false;
    this->time_start=0;
    this->isPause = nota.is_pause;
    next = nullptr;
}

int MNota::getDur()
{
    return dur;
}
