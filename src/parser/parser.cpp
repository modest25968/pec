#include "parser.h"

#include <QDir>
#include <QDebug>
#include <QtXml>
#include <QMessageBox>
#include <QtXmlPatterns>

#include "../core/xmlbasesong.h"


XmlParser::XmlParser():
    errorText("")
{
    ok = true;
}

bool XmlParser::parse(QString filename, XmlBaseSong *gsong, XmlBaseSong *msong)
{
    qDebug()<<"Start ";
    errorText = "";
    ok = true;
    QXmlStreamReader* xml = openFile(filename);

    double version = -1;
    version = findVersion(*xml);

    if (version == 1.1 || version == 2)
    {
        parseCPe11(*xml, gsong, msong, version);
    }
    delete xml;
    return false;
}

QXmlStreamReader* XmlParser::openFile(QString filename)
{
    QFile* file = new QFile(filename);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"ERROR open xml file";
        return nullptr;
    }

    QXmlStreamReader* xml = new QXmlStreamReader(file);
    return xml;
}


void XmlParser::parseCPe11(QXmlStreamReader &xml, XmlBaseSong *gsong, XmlBaseSong *msong, double version)
{

    int tempo = 90;
    bool isXmlHaveTempo = false;

    //FIXME: crutch
    if (xml.name() == "tempo")
    {
        xml.readNext();
        tempo = xml.text().toInt();
        xml.readNext();
        isXmlHaveTempo = true;
    }

    parsePart(xml, gsong, msong, version);

    ok = true;
    if (isXmlHaveTempo)
    {
    if (msong != nullptr)
        msong->setTempo(tempo);
    }
    else
        qWarning()<<"song DONT HAVE TEMPO";

}

void XmlParser::parsePart(QXmlStreamReader &xml, XmlBaseSong *gsong, XmlBaseSong *msong, double version)
{
    int numPart = 0;
    Snote nota;
    Satr atr;

    int tdur, tback;
    tdur = 0;

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "part")
            {
                numPart++;
                nota.part = numPart;
                if (gsong != nullptr){gsong->createNextPart();}
                tdur = 0;
            }

            if (xml.name() == "measure")
            {
                if (gsong != nullptr) gsong->createNextMissure();
                tdur = 0;
            }

            if (xml.name() == "note")
            {
                nota = parseNote(xml, version);
                nota.part = numPart;
                if (msong != nullptr) msong->createAddNota(nota);
                if (gsong != nullptr) gsong->createAddNota(nota);
            }

            if (xml.name() == "attributes")
            {
                atr = parseAtr(xml, version);
                if (gsong != nullptr) gsong->createAddAtr(atr);
            }

            if (xml.name() == "backup")
            {
                xml.readNext();
                xml.readNext();
                tback = xml.text().toInt();
                xml.readNext();
                tdur -= tback;
            }
        }

        if (token == QXmlStreamReader::EndElement)
        {

            if (xml.name() == "measure")
            {
                if (gsong != nullptr) gsong->createEndMissure();
            }

            if (xml.name() == "part")
            {
                if (gsong != nullptr) gsong->createEndPart();
                if (msong != nullptr) msong->createEndPart();
            }
        }
    }
}


Snote XmlParser::parseNote(QXmlStreamReader &xml, double version)
{
    Q_UNUSED(version);
    Snote note;
    \
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "note")
        {
            note.midi = note.midi_temp+note.oct*12 + note.alter;
            return note;
        }

        else if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "rest")
                note.is_pause = true;

            else if (xml.name() == "chord")
                note.in_chord = true;

            else if (xml.name() == "notations")
            {
                xml.readNext();
                xml.readNext();
                if (xml.name() != "tied")
                {
                    //TODO::lur!!
                }
                if (!xml.attributes().isEmpty() && xml.attributes().value("type").toString()=="start")
                {
                    note.tied = 1;
                }
                else if (!xml.attributes().isEmpty() && xml.attributes().value("type").toString()=="stop")
                {
                    note.tied = 2;
                }
                else
                    qDebug()<<"Неизвестный знак между нотами (notations)";

                xml.readNext();

            }

            else if (xml.name() == "stem")
            {
                xml.readNext();
                if (xml.text() == "up") note.stem = 1;
                else note.stem = 0;
                xml.readNext();
            }

            else if (xml.name() == "alter")
            {
                readIntXmlVal(xml, note.alter);
            }

            else if (xml.name() == "accidental")
            {
                xml.readNext();
                if      (xml.text() == "sharp")   note.accidental = 1;
                else if (xml.text() == "flat")    note.accidental = 2;
                else if (xml.text() == "natural") note.accidental = 3;
                else
                {
                    qDebug()<<"Неизвестный знак перед нотой "+xml.text().toString();
                }
                xml.readNext();
            }

            else if (xml.name() == "voice")
            {
                readIntXmlVal(xml, note.voice);
            }

            else if (xml.name() == "duration")
            {
                readIntXmlVal(xml, note.dur);
                note.dur = note.dur * 480 / divisions;
            }

            else if (xml.name() == "octave")
            {
                readIntXmlVal(xml, note.oct);
            }

            else if (xml.name() == "step")
            {
                xml.readNext();
                if       (xml.text() == "A") {note.step = 1;note.midi_temp = 21;}
                else if  (xml.text() == "B") {note.step = 2;note.midi_temp = 23;}
                else if  (xml.text() == "C") {note.step = 3;note.midi_temp = 12;}
                else if  (xml.text() == "D") {note.step = 4;note.midi_temp = 14;}
                else if  (xml.text() == "E") {note.step = 5;note.midi_temp = 16;}
                else if  (xml.text() == "F") {note.step = 6;note.midi_temp = 17;}
                else if  (xml.text() == "G") {note.step = 7;note.midi_temp = 19;}
                else
                    qDebug()<<"Неизвесная нота "+xml.text().toString();
            }
        }
    }
    qDebug()<<"Not found </note>";
    errorText = "Not found tag </note>";
    ok = false;
    return note;
}

double XmlParser::findVersion(QXmlStreamReader &xml)
{
    double version = -1;
    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();
        if (xml.name() == "score-partwise")
        {
            if ((xml.attributes().size()==1)&&(xml.attributes()[0].name()=="version"))
            {
                version = xml.attributes()[0].value().toDouble();
                xml.readNext();
                xml.readNext();
            }
            break;
        }
    }
    qDebug()<<"MUSXML ver:"<<version;
    if (version == -1)
    {
        qDebug()<<"Не удалось распознать MUSICXML";
        ok = false;
        errorText = "Не удалось распознать версию MUSICXML";
    }
    if (version != 1.1 && version != 2)
    {
        qDebug()<<"неизвестная версия MUSICXML:" << version;
        ok = false;
        errorText = "Нет поддержки MUSICXML версии "+QString::number(version);
    }

    return version;

}

Satr XmlParser::parseAtr(QXmlStreamReader &xml, double version)
{
    Q_UNUSED(version);
    Satr atr;
    \
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "attributes")
        {
            return atr;
        }

        if (token == QXmlStreamReader::StartElement)
        {

            if (xml.name() == "divisions")
            {
                readIntXmlVal(xml, atr.divisions);
                divisions = atr.divisions;
            }

            else if (xml.name() == "fifths")
            {
                readIntXmlVal(xml, atr.ton_fifths);
            }

            else if (xml.name() == "beats")
            {
                readIntXmlVal(xml, atr.beats);
            }

            else if (xml.name() == "beat-type")
            {
                readIntXmlVal(xml, atr.beattype);
            }

            else if (xml.name() == "line")
            {
                readIntXmlVal(xml, atr.clef_line);
            }

            else if (xml.name() == "sign")
            {
                xml.readNext();
                if (xml.text() == "G")
                    atr.clef_sign = 0;
                else if (xml.text() == "F")
                    atr.clef_sign = 1;
                else
                    qDebug()<<"Неизвестный ключ: "+xml.text().toString();
            }
        }
    }
    qDebug()<<"Not found </attributes>";
    errorText = "Not found tag </attributes>";
    ok = false;

    return atr;
}

void XmlParser::readIntXmlVal(QXmlStreamReader &xml, int &to)
{
    xml.readNext();
    to = xml.text().toInt();
    xml.readNext();
}
