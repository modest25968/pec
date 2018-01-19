#include "rtback.h"

#include "rtmidi.h"

#include <windows.h>
#include <QDebug>

Rtback::Rtback()
{
    midiout = new RtMidiOut();
    std::vector<unsigned char> message;
    // Check available ports.
    unsigned int nPorts = midiout->getPortCount();
    if ( nPorts == 0 ) {
      std::cout << "No ports available!\n";
      ready = false;
    }
    ready = true;
    // Open first available port.
    midiout->openPort( 0 );
    message.push_back(0);
    message.push_back(0);
    for (int i=192;i<198;i++)
    {
        message[0] = i;
        message[1] = 32;
        midiout->sendMessage( &message );
    }
}

Rtback::~Rtback()
{
    delete midiout;
}

void Rtback::note_on(int chan, short key)
{   
    std::vector<unsigned char> message;
    message.push_back( 144+chan );
    message.push_back( key );
    message.push_back( 90 );
    midiout->sendMessage( &message );

}

void Rtback::note_off(int chan, short key)
{
    std::vector<unsigned char> message;
    message.push_back( 128+chan );
    message.push_back( key );
    message.push_back( 40 );
    midiout->sendMessage( &message );
}

void Rtback::notes_off()
{

}

void Rtback::set_volume(int chan, int vol)
{
    qDebug()<<chan<< "volume="<<vol;
    std::vector<unsigned char> message;
    message.push_back( 176+chan );
    message.push_back( 7 );
    message.push_back( vol );
    midiout->sendMessage( &message );
}

void Rtback::test()
{
    std::vector<unsigned char> message;
    message.push_back( 192 );
    message.push_back( 5 );
    midiout->sendMessage( &message );


    // Control Change: 176, 7, 100 (volume)
    message[0] = 176;
    message[1] = 7;
    message.push_back( 100 );
    midiout->sendMessage( &message );
    // Note On: 144, 64, 90

    for (int i=192;i<198;i++)
    {
        message[0] = i;
        message[1] = 32;
        midiout->sendMessage( &message );
    }

    note_on(0,64);
    Sleep( 500 ); // Platform-dependent ... see example in tests directory.
    // Note Off: 128, 64, 40
    note_off(0  ,64);

}
