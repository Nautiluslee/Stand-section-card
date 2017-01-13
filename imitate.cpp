#include "imitate.h"
#include "screen.h"

extern universdata *ud;

imitate::imitate(QObject *parent) :
    QThread(parent)
{
    //qDebug()<<"Creatting Thread Loop";
}

void imitate::run()
{
    int i=0;
    QString hint = "下一站，";
    while(i<ud->numsofstation)
    {
        hint.append(ud->station[i]);
        sleep(3);
        emit NextStation(hint);
        sleep(5);
        //emit SwitchStation();
        //sleep(3);
        emit ArrivedStation();
        sleep(5);
        hint.remove(4,ud->station[i].length());
        i++;
    }
}


