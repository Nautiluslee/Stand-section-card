#ifndef UNIVERSDATA_H
#define UNIVERSDATA_H
#include <QString>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QTextStream>


class universdata
{
public:
    universdata();

    struct ModeParam
    {
        int Mode;//显示模式
        QString resourcesPath;
        int numsOfStation,numsOfSwitchStation;

        QString lineNum;//线路名称
        QString subLineNum;//子线路名

        QString bkgPicName;
        int bkgPicHeight,bkgPicWidth,bkgPicRectWidth,bkgPicRectHeight,containerLabelPosY;

        int roundLabelDiameter;
        QString roundLabelborderRadius;
        QString roundLabelColorPassed;//圆标，已过站颜色
        QString roundLabelColorArrived;//圆标，达站颜色
        QString roundLabelColorNonarrival;//圆标，将到站颜色
        QString roundLabelFontSize;

        QString textLabelBkg;//站标，背景
        int textLabelWidth,textLabelHeight;
        QString textLabelColorNonarrival;//站标，将到站颜色
        QString textLabelColorPassed;//站标，已过站颜色
        QString textLabelFontSize;//站标，字体大小

        QString informPageBkg;
    };

    QString cfgFileName;
    QSettings *cfg;

    int linenum,sublinenum,numsofstation;
    QString cfg_textFileDir,picDir;
    QString startToTerminal;
    QList<QString>station;
    QList<QString>switchstations;

    ModeParam *mp;
};

#endif // UNIVERSDATA_H
