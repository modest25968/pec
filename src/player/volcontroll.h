#ifndef VOLCONTROLL_H
#define VOLCONTROLL_H

#include <QObject>
class AbstractBackend;

class VolControll : public QObject
{
    Q_OBJECT
public:
    explicit VolControll(QObject *parent = nullptr);
    void setAb(AbstractBackend* ab);
    void setCountVoice(int cv);
signals:
    void countChange(int newCount);
public slots:
    void setVolume(int chan, int vol);


private:
    int nv;
    int volums[16];
    AbstractBackend* ab;
};

#endif // VOLCONTROLL_H
