#ifndef PARSER_H
#define PARSER_H

#include <QString>


class QXmlStreamReader;

class XmlBaseSong;
class Snote;
class Satr;
class OpenTest;

class XmlParser
{
public:
    XmlParser();
    bool parse(QString filename, XmlBaseSong *gsong=nullptr, XmlBaseSong *msong=nullptr);
    bool ok;
    QString errorText;
    friend OpenTest;
private:
    QXmlStreamReader* openFile(QString filename);
    void parseCPe11(QXmlStreamReader &xml, XmlBaseSong *gsong, XmlBaseSong *msong, double version);
    void parsePart(QXmlStreamReader &xml, XmlBaseSong *gsong, XmlBaseSong *msong, double version);
    double findVersion(QXmlStreamReader &xml);
    Snote parseNote(QXmlStreamReader &xml, double version);
    Satr parseAtr(QXmlStreamReader &xml, double version);

    void readIntXmlVal(QXmlStreamReader &xml, int &to);

    int divisions;
};



#endif // PARSER_H
