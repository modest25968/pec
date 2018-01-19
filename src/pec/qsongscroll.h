#ifndef QSONGSCROLL_H
#define QSONGSCROLL_H

#include <QFrame>

class QSongScroll : public QFrame
{
    Q_OBJECT
public:
    explicit QSongScroll(QWidget *parent = nullptr);

    virtual QSize sizeHint() const;
signals:
    void newTime(int time);
public slots:
    void songChange(int dur);
    void tickEvent();
    void update(int newTime, int newTimeS, int newTimeE);
    void update();
private:
    int x,y,h,w;
    int dur;
    int tekPol;
    int time;
    int timeStartCi;
    int timeEndCi;
    bool lcl;
    int tempTime;
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent (QMouseEvent* pe);
    virtual void mouseMoveEvent (QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);

};

#endif // QSONGSCROLL_H
