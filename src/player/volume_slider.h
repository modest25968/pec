#ifndef VOLUME_SLIDER_H
#define VOLUME_SLIDER_H

#include <QObject>
#include <QSlider>

class VolumeSlider : public QSlider
{
    Q_OBJECT
public:
    VolumeSlider(int channel, QWidget* parent = nullptr);
    int getChannel();
private:
    int channel;
signals:
    void signalVolumeChange(int channel, int volume);
public slots:
    void slotVolumeChange(int volume);
};

#endif // VOLUME_SLIDER_H
