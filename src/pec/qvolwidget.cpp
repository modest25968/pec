#include "qvolwidget.h"
#include <QCheckBox>
#include <QLabel>
#include "../player/volume_slider.h"

class MyQCheckBox :  public QCheckBox
{
public:
    MyQCheckBox(QString caption, int channel, QWidget* parent):
        QCheckBox(caption, parent)
    {
        this->channel = channel;
    }


    int channel;
};

VolumeWidget::VolumeWidget(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    this->setLayout(grid);
    for (int i=0;i<16;i++)
    {
        volums[i] = 127;
        enabled[i] = true;
    }

}

void VolumeWidget::setCount(int count)
{
    this->count = count;
    deletePanels();
    createPanels();
}

void VolumeWidget::SlotsetVolume(int chan, int vol)
{
    this->volums[chan] = vol;
    emit setVolume(chan, vol);
}

void VolumeWidget::setChannelEnable(bool enabled)
{
    MyQCheckBox* sender = dynamic_cast<MyQCheckBox*>(QObject::sender());
    //Volume_Slider* ob = dynamic_cast<Volume_Slider*>(sender->parent());
    int chan = sender->channel;
    this->enabled[chan] = enabled;
    if (enabled)
        emit setVolume(chan, volums[chan]);
    else
        emit setVolume(chan, 0);
}


void VolumeWidget::createVolumePanel(int channel, int volume, QString caption)
{
    VolumeSlider* slider = new VolumeSlider(channel, this);
    slider->setOrientation(Qt::Horizontal);
    slider->setMaximum(127);
    slider->setValue(volume);

    MyQCheckBox* but = new MyQCheckBox(caption, channel, slider);
//    but->channel = channel;
//    but->setChecked(true);
     but->setChecked(enabled[channel]);
     slider->setEnabled(enabled[channel]);
//    but->setText("1");

    connect(but, SIGNAL(toggled(bool)),
            slider, SLOT(setEnabled(bool)));

    connect(but, SIGNAL(toggled(bool)),
            SLOT(setChannelEnable(bool)));

    connect(slider, SIGNAL(signalVolumeChange(int,int)),
            this, SLOT(SlotsetVolume(int,int)));

    //QLabel* lab = new QLabel(caption, this);

    grid->addWidget(but, channel, 1);
    grid->addWidget(slider, channel, 2);
}

void VolumeWidget::deletePanels()
{

    for (int i=0;i<grid->rowCount();i++)
        for (int j=0;j<grid->columnCount();j++)
        {
            if (grid->itemAtPosition(i,j))
            {
                delete(grid->itemAtPosition(i,j)->widget());
            }
        }
}

void VolumeWidget::createPanels()
{
    for (int i=0;i<count;i++)
    {
        createVolumePanel(i, volums[i], QString::number(i+1));
    }
}
