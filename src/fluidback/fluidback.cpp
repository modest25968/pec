#include "fluidback.h"
#include <QDebug>

Fluidback::Fluidback()
{
    for (int i=0;i<16;i++)
        volumes.push_back(127);

    qDebug()<<"start create fluidplayer";
    createsynth();
    qDebug()<<"start load sf2";
    loadsoundfont();
}

void Fluidback::noteOn(int chan, short key)
{
    fluid_synth_noteon(synth, chan, key, volumes[chan]);
}

void Fluidback::noteOff(int chan, short key)
{
    fluid_synth_noteoff(synth, chan, key);
}

void Fluidback::notesOff()
{
    for (int chan=0;chan<16;chan++)
        fluid_synth_all_notes_off(synth, chan);
}

void Fluidback::setVolume(int chan, int vol)
{
    (volumes)[chan] = vol;
    //fluid_synth_cc(synth, chan, 7, vol);
}

void Fluidback::resetVolume(int newVol)
{
    for (int i=0;i<16;i++)
    {
        fluid_synth_cc(synth, i, 7, newVol);
    }
}

void Fluidback::createsynth()
{

    fluid_settings_t* settings;
    int flag;

    qDebug()<<"createsynth";
    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "pulseaudio");
    fluid_settings_setstr(settings, "synth.verbose", "yes");
    fluid_settings_setstr(settings, "synth.reverb.active", "no");
    //    fluid_synth_set_reverb(synth,0.2,0.2,1,0.2);
    fluid_settings_setstr(settings, "synth.chorus.active", "no");

    fluid_settings_setint(settings, "audio.realtime-prio", 100);

    synth = new_fluid_synth(settings);

#ifdef Q_OS_ANDROID
    fluid_settings_setint(settings, "synth.cpu-cores", 4);
    fluid_settings_setint(settings, "audio.opensles.use-callback-mode", 1);
#endif


#ifdef Q_OS_ANDROID
    fluid_settings_setint(settings, "synth.cpu-cores", 4);
    fluid_settings_setint(settings, "audio.opensles.use-callback-mode", 1);
#endif

#ifdef Q_OS_WIN32
    fluid_settings_setstr(settings, "audio.driver", "dsound");
#endif

    qDebug()<<"create settings ok";
    qDebug()<<"create synth ok";
    flag = fluid_synth_sfcount(synth);
    qDebug()<<flag;
    adriver = new_fluid_audio_driver(settings, synth);


    qDebug()<<"create adriver, seq ok. ID:"<<synthSeqID;


    for (int ch=0;ch<16;ch++)
    {
        fluid_synth_bank_select(synth, ch, 1);
        fluid_synth_program_change(synth, ch, 16);
    }
    qDebug()<<"set programm ok";

    fluid_synth_set_channel_type(synth, 9, 1);//channel9 - drum
    fluid_synth_program_reset(synth);
    qDebug()<<"reset ok";
    resetVolume(127);
}

void Fluidback::loadsoundfont()
{
    int flag = fluid_synth_sfload(synth, "1.sf2", 1);
    if (flag!=-1)
    {
        qDebug()<<"load soundfont OK";
        return;
    }
    flag = fluid_synth_sfload(synth, "/sdcard/1.sf2", 1);
    if (flag!=-1)
    {
        qDebug()<<"load soundfont OK";
        return;
    }

    flag = fluid_synth_sfload(synth, "/sdcard2/1.sf2", 1);
    if (flag!=-1)
    {
        qDebug()<<"load soundfont OK";
        return;
    }

    qDebug()<<"Error in load soundfont";
    textError = "soundfont load failure";
}
