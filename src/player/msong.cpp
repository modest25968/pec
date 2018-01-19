#include "msong.h"
//#include "player.h"
#include <QDebug>
#include <QObject>

#include "../core/abstractbackend.h"

MSong::MSong(QObject *parent)
{
    name = "No Name";
    Q_UNUSED(parent);
    tempo = 96;
    time = 0;
    dur = -1;
    isLooping = false;
}

MSong::~MSong()
{

}

void MSong::setPl(AbstractBackend* player)
{
    ab = player;
}

int MSong::getTempo()
{
    return tempo;
}

int MSong::getCountVoice()
{
    return partNotes.size();
}

int MSong::getDur()
{
    if (dur!=-1)
        return dur;

    QVector<int> vdur;
    for (int i=0;i<partNotes.size();i++)
    {
        vdur.push_back(0);
        int cn = partNotes[i].size();
        for (int j=0;j<cn;j++)
        {
            if (!partNotes[i][j]->next_in_chord)
                vdur.last() += partNotes[i][j]->dur;
        }
    }
    for (int i=0;i<vdur.size();i++)
        qDebug()<<"voice "<<i<<" dur ="<<vdur[i];

    dur = vdur[0];
    return dur;
}

QString MSong::getName()
{
    return name;
}

bool MSong::getLooping()
{
    return isLooping;
}

void MSong::setTempo(int new_tempo)
{
    this->tempo = new_tempo;
}

void MSong::createEndMissure()
{
    partNotes[0].last()->end_takt = true;
}

void MSong::createAddNota(Snote nota)
{
    int pos = nota.part * 10+nota.voice;
    if (!map.contains(pos))
    {
        partNotes.append(QVector<MNota*>());
        map.insert(pos, partNotes.size()-1);
    }
    int part = map[pos];
    MNota* mnota = new MNota(nota);

    partNotes[part].append(mnota);
}

void MSong::setStart()
{
    time = timeStartCi;
    findNowNota(time);
    updateScroll(time, timeStartCi, timeEndCi);
}

void MSong::tick()
{
    qDebug()<<"TICK2!!!";

    bool next_takt_after = false;
    int part_size = partNotes.size();

    if (time == timeStartCi)
    {
        findNowNota(time);
        playTekNotes();
        time +=120;
        return;
    }

    checkEndCi();

    int nNote;
    bool end = false;

    for (int voice = 0;voice < part_size;voice++)
    {
        nNote = tekNotes[voice];
        MNota* tNota = partNotes[voice][nNote];
        if (tNota->time_start+tNota->getDur() <= time)
        {
            notaOff(tNota,voice);

            nNote ++;
            if (nNote == partNotes[voice].size())
            {
                qDebug()<<"end song";
                end = true;
            }
            else
            {
                tekNotes[voice] ++;
                notaOn(partNotes[voice][nNote], voice);
            }
        }
    }



    if (end)
    {
        emit songEnd();
        return;
    }

    if (next_takt_after)
        qDebug()<<"next takt";

    time += 120;
    updateScroll(time, timeStartCi, timeEndCi);
}

void MSong::stopPlay()
{
    int part_size = partNotes.size();
    if (tekNotes.size() == part_size)
    for (int voice = 0;voice < part_size;voice++)
    {
        int nNote = tekNotes[voice];
        MNota* tNota = partNotes[voice][nNote];
        notaOff(tNota, voice);
    }
}

void MSong::setTime(int time)
{
    stopPlay();
    tekNotes.clear();
    this->time = time;
    findNowNota(time);
    playTekNotes();
}

void MSong::setStartCi()
{
    if (timeStartCi == 0)
        timeStartCi = time;
    else
        timeStartCi = 0;
    updateScroll(time, timeStartCi, timeEndCi);
}

void MSong::setEndCi()
{
    if (timeEndCi == dur)
        timeEndCi = time;
    else
        timeEndCi = dur;
    updateScroll(time, timeStartCi, timeEndCi);
}

void MSong::setEnabledCi(bool enabled)
{
    isLooping = enabled;
}

void MSong::init()
{
    //init next note
    for (int i=0;i<partNotes.size();i++)
    {
        for (int j=0;j<partNotes[i].size()-1;j++)
        {
            partNotes[i][j]->next = partNotes[i][j+1];
        }
    }

    //init start time for notes
    for (int i=0;i<partNotes.size();i++)
    {
        int t =0;
        for (int j=0;j<partNotes[i].size();j++)
        {
            partNotes[i][j]->time_start = t;
            if (!partNotes[i][j]->next_in_chord)
                t+=partNotes[i][j]->dur;
        }
    }

    timeStartCi = 0;
    timeEndCi = getDur();
    emit setSongForScroll(timeEndCi);//, &time, &timeStartCi, &timeEndCi);
}

void MSong::findNowNota(int time)
{
    tekNotes.clear();
    for (int i=0;i<partNotes.size();i++)
    {
        for (int j=0;j<partNotes[i].size();j++)
        {
            if (partNotes[i][j]->time_start+partNotes[i][j]->getDur()>time)
            {
                tekNotes.append(j);
                break;
            }
        }
    }
}

void MSong::playTekNotes()
{
    for (int i=0;i<tekNotes.size();i++)
    {
        MNota* nota = partNotes[i][tekNotes[i]];
        notaOn(nota, i);
    }

}

void MSong::notaOn(MNota *nota, int channel)
{
    MNota* tnota=nota;
    int k=0;
    do
    {
        if (k!=0)
            tnota = tnota->next;

        if (!tnota->isPause)
            ab->noteOn(channel, tnota->midi);
        k++;
    }
    while (tnota->next_in_chord);
}

int MSong::notaOff(MNota *nota, int channel)
{
    int k=0;
    MNota* tnota=nota;
    do
    {
        if (k!=0)
            tnota = tnota->next;
        if (!tnota->isPause)
            ab->noteOff(channel, nota->midi);
        k++;
    }
    while (tnota->next_in_chord);

    if (nota->time_start+nota->dur != time)
    {
        qDebug()<<"WTF you won't stop note, which not in the end. Stop it please";
    }
    return k;
}

void MSong::checkEndCi()
{
    if (time >= timeEndCi)
    {
        stopPlay();
        setStart();
        if (!isLooping)
        {
            emit songEnd();
        }
        return;
    }
}
