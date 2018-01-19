#include "qsongscroll.h"

#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>

#include <QDebug>

void QSongScroll::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;

    painter.setPen(Qt::NoPen);
    int cy;
    int time;
    if (lcl)
        time = this->tempTime;
    else
        time = this->time;

    x = rect().x();
    y = rect().y();
    w = rect().width();
    h = rect().height();
    int st_x, end_x;
    st_x = x + ((timeStartCi)*w) / dur;
    end_x = x + ((timeEndCi)*w) / dur;

    tekPol = x + ((time)*(w))/dur;

    cy = y+h/2;
    painter.drawLine(x,cy,x+w,cy);

    QLinearGradient gradient (0, 0, tekPol-x, h);
    gradient.setColorAt (0, Qt::blue);
    gradient.setColorAt (1, Qt::cyan);
    painter.setBrush(gradient);

    painter.drawRect(st_x,y,tekPol-st_x, h);

    QLinearGradient gr2(tekPol-x, 0, end_x-tekPol, h);
    gr2.setColorAt(0, Qt::cyan);
    gr2.setColorAt(1, Qt::blue);
    painter.setBrush(gr2);
    painter.drawRect(tekPol,y,end_x-tekPol, h);

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(tekPol, y, tekPol, y + h);

    pen.setWidth(1);
    pen.setColor("black");
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(x,y,x+w-1,y+h-1);
}

void QSongScroll::mousePressEvent(QMouseEvent *pe)
{
    lcl = false;

    if (pe->button() == 1) //left mouse
    {
        int xc = pe->x();
        tempTime = ((xc-x)*dur)/w;
        if (tempTime<(timeStartCi)) tempTime = (timeStartCi);
        if (tempTime>(timeEndCi)) tempTime = (timeEndCi);
        lcl = true;
        update();
    }
}

void QSongScroll::mouseMoveEvent(QMouseEvent *pe)
{
    if (lcl)
    {
        int xc = pe->x();
        tempTime = ((xc-x)*dur)/w;
        if (tempTime<(timeStartCi)) tempTime = (timeStartCi);
        if (tempTime>(timeEndCi)) tempTime = (timeEndCi);
        update();
    }
}

void QSongScroll::mouseReleaseEvent(QMouseEvent *pe)
{
    Q_UNUSED(pe);
    if (lcl)
    {
        qDebug()<<"new time"<<tempTime;
        time = tempTime;
        emit newTime(tempTime);
    }
    lcl = false;
}

QSize QSongScroll::sizeHint() const
{
    return QSize(200,30);
}

QSongScroll::QSongScroll(QWidget *parent) : QFrame(parent)
{
    setLineWidth (3);
    setFrameStyle(Box);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    time = 0;
    dur = 100;
    timeStartCi = 0;
    timeEndCi = dur;
}

void QSongScroll::songChange(int dur)
{
    time = 0;
    this->dur = dur;
    timeStartCi = 0;
    timeEndCi = dur;
}

void QSongScroll::tickEvent()
{
    update();
}

void QSongScroll::update(int newTime, int newTimeS, int newTimeE)
{
    this->time = newTime;
    this->timeStartCi = newTimeS;
    this->timeEndCi = newTimeE;
    update();
}

void QSongScroll::update()
{
    repaint();
}
