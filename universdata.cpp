#include "universdata.h"

universdata::universdata()
{
    cfg_textFileDir = "/opt/dvr_rdk/ti810x/qtTest/1000036/";
    picDir = "/opt/dvr_rdk/ti810x/qtTest/pictures/";

    cfg = new QSettings(cfg_textFileDir + "configure1.ini",QSettings::IniFormat);//打开配置文件
    cfg->setIniCodec("UTF8");
    //qDebug()<<"New Memory For Struct ModeParam";
    mp = new ModeParam();

    mp->Mode = cfg->value("/Generals/Mode").toInt();

    mp->lineNum = cfg->value("/StationInfo/LineNum").toString();
    //linenum = mp->lineNum.toInt();
    mp->subLineNum = cfg->value("/StationInfo/SubLineNum").toString();
    //sublinenum = mp->subLineNum.toInt();

    mp->numsOfStation = 0;

    mp->bkgPicName = cfg->value("/ContainerLabelInfo/BkgPicName").toString();
    mp->bkgPicHeight = cfg->value("/ContainerLabelInfo/BkgPicHeight").toInt();
    mp->bkgPicWidth = cfg->value("/ContainerLabelInfo/BkgPicWidth").toInt();
    mp->bkgPicRectWidth = cfg->value("/ContainerLabelInfo/BkgPicRectWidth").toInt();
    mp->bkgPicRectHeight = cfg->value("/ContainerLabelInfo/BkgPicRectHeight").toInt();
    mp->containerLabelPosY = cfg->value("/ContainerLabelInfo/ContainerLabelPos_Y").toInt();

    mp->roundLabelDiameter = cfg->value("/RoundLabelInfo/Diameter").toInt();
    mp->roundLabelborderRadius = cfg->value("/RoundLabelInfo/BorderRadius").toString();
    mp->roundLabelColorPassed = cfg->value("/RoundLabelInfo/ColorPassed").toString();
    mp->roundLabelColorArrived = cfg->value("/RoundLabelInfo/ColorArrived").toString();
    mp->roundLabelColorNonarrival = cfg->value("/RoundLabelInfo/ColorNonarrival").toString();
    mp->roundLabelFontSize = cfg->value("/RoundLabelInfo/FontSize").toString();


    mp->textLabelBkg = cfg->value("/TextLabelInfo/Background").toString();
    mp->textLabelWidth = cfg->value("/TextLabelInfo/Width").toInt();
    mp->textLabelHeight = cfg->value("/TextLabelInfo/Height").toInt();
    mp->textLabelColorNonarrival = cfg->value("/TextLabelInfo/TextColorNonarrival").toString();
    mp->textLabelColorPassed = cfg->value("/TextLabelInfo/TextColorPassed").toString();
    mp->textLabelFontSize = cfg->value("/TextLabelInfo/FontSize").toString();

    mp->informPageBkg = cfg->value("/InformPage/bkgPicName").toString();

    QFile filestations(cfg_textFileDir + "stationup.txt");//打开站点名文件
    filestations.open(QFile::ReadOnly);
    QTextStream ins(&filestations);
    while(!ins.atEnd())
    {
        QString stations=ins.readLine();
        station.append(stations);
        mp->numsOfStation++;//可直接=station.size();
    }
    startToTerminal = station[0] + "->" + station[station.size()-1];//配置始末站
    filestations.close();
    numsofstation = station.size();

    mp->numsOfSwitchStation = mp->numsOfStation;//换乘站文本内行数=站点数

    QFile fileswitchstations(cfg_textFileDir + "switchstationsup.txt");//打开换乘站文件
    fileswitchstations.open(QFile::ReadOnly);
    QTextStream inss(&fileswitchstations);
    QString ss;
    while(!inss.atEnd())
    {
        ss = inss.readLine();
        switchstations.append(ss);
    }
    fileswitchstations.close();
}

