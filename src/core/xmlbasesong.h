#ifndef XMLBASESONG_H
#define XMLBASESONG_H
#include <QObject>

struct Snote
{
    Snote ():
        accidental(0),
        tied(0),
        alter(0),
        in_chord(false),
        is_pause(false)
    {}

    int accidental;
    int step;
    int oct;
    int dur;
    int stem;
    int voice;
    int tied;
    int alter;
    int midi;
    int midi_temp;
    bool in_chord;
    bool is_pause;
    int part;
};

struct Satr
{
    int beats, beattype, divisions, clef_line, ton_fifths;
    char clef_sign;
};

class XmlBaseSong :public QObject
{
public:

    explicit XmlBaseSong(QObject *parent = 0 /* unused */){
        Q_UNUSED(parent);
    }
    ~XmlBaseSong(){};

    virtual void createNextPart()=0;
    virtual void createEndPart()=0;

    virtual void createNextMissure()=0;
    virtual void createEndMissure()=0;



    //virtual void create_next_voice()=0;

    virtual void createAddNota(Snote nota)=0;
    virtual void createAddAtr(Satr atr)=0;
    void setTempo(int tempo) {this->tempo = tempo;}
    int getTempo() {return tempo;}

protected:
    int tempo;
};

#endif // XMLBASESONG_H
