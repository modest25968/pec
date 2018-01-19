#include "volume_slider.h"

VolumeSlider::VolumeSlider(int channel, QWidget* parent): QSlider(parent)
{
    this->channel = channel;
    QObject::connect(this, SIGNAL(valueChanged(int)),
                     this, SLOT(slotVolumeChange(int)));
}

int VolumeSlider::getChannel()
{
    return channel;
}

void VolumeSlider::slotVolumeChange(int volume)
{
    emit signalVolumeChange(channel, volume);
}
