#include "mylabel.h"
#include "screen.h"

int blinkCount=0;
extern universdata *ud;

MyLabel::MyLabel(QWidget * parent) : QLabel(parent)
{
    configParam();

    setStyleSheet(nonarrivalStyleSheet);
    setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
}

void MyLabel::configParam()
{
    defaultStyleSheet = "QLabel{background:transparent;border-radius:;background-color:;font:;color:;}";//43,61,67,88
    nonarrivalStyleSheet=defaultStyleSheet.insert(44,ud->mp->roundLabelborderRadius).insert(66,ud->mp->roundLabelColorNonarrival).insert(77,ud->mp->roundLabelFontSize).insert(88,"black");
    passedStyleSheet = defaultStyleSheet.remove(66,5).insert(66,ud->mp->roundLabelColorPassed).remove(88,5).insert(88,"white");
    arrivedStyleSheet = defaultStyleSheet.remove(66,5).insert(66,ud->mp->roundLabelColorArrived).remove(85,5).insert(85,"black");
}

void MyLabel::Blink()
{
    tm = new QTimer(this);
    connect(tm,SIGNAL(timeout()),this, SLOT(toBlink()));
    tm->start(500);
}

void MyLabel::toBlink()
{
    setStyleSheet(styleSheet()==arrivedStyleSheet?passedStyleSheet:arrivedStyleSheet);
    blinkCount++;
    if(blinkCount==6)
    {
        tm->stop();
        emit nextStation();
        blinkCount=0;
    }
}


