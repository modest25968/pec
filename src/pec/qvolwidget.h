#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include <QGridLayout>
#include <QWidget>

class VolumeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeWidget(QWidget *parent = nullptr);

signals:
    void setVolume(int chan, int vol);
public slots:
    void setCount(int count);
    void SlotsetVolume(int chan, int vol);
    void setChannelEnable(bool enabled);
private:
    void createVolumePanel(int channel, int volume, QString caption);
    int count;
    int volums[16];
    bool enabled[16];
    void deletePanels();
    void createPanels();

    QGridLayout* grid;
};

#endif // VOLUMEWIDGET_H
