#include "screen.h"
#include "ui_screen.h"

int i,blinkcount,textchangecolorcount,pagecount,switchcount;
universdata *ud = new universdata();

screen::screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::screen)
{
    ui->setupUi(this);

    ui->black->setStyleSheet("QLabel{border-image: url(/opt/dvr_rdk/ti810x/qtTest/pictures/blackpoint.jpg);background:transparent;}");
    ui->red->setStyleSheet("QLabel{border-image: url(/opt/dvr_rdk/ti810x/qtTest/pictures/redpoint.jpg);background:transparent;}");

    pagecount=0;
    i=0;
    blinkcount=0;
    switchcount=0;

    configParam();

    switch(ud->mp->Mode)
    {
        case 1:loadMode1();break;
        case 2:loadMode2();break;
        case 3:loadMode3();break;
    }

    imitate *loop = new imitate();
    loop->start();
    connect(loop,SIGNAL(NextStation(QString)),this,SLOT(nextStationPage(QString)));
    //connect(loop,SIGNAL(SwitchStation()),this,SLOT(switchStationsPage()));
    connect(loop,SIGNAL(ArrivedStation()),this,SLOT(blinkNext()));

}

screen::~screen()
{
    delete ui;
}

void screen::configParam()
{
    //qDebug()<<"in configparam()";
    containerLabelX = (this->width()-ud->mp->bkgPicWidth)/2;
    containerLabelY = ud->mp->containerLabelPosY;
    containerLabelWidth = ud->mp->bkgPicWidth;
    containerLabelHeight = ud->mp->bkgPicHeight;
    containerLabelGeometry = QRect(containerLabelX,containerLabelY,containerLabelWidth,containerLabelHeight);//mode1容器label位置

    if(ud->mp->Mode==1)
    {
        mode1RoundLabelPosY = ud->mp->containerLabelPosY + (ud->mp->bkgPicHeight-ud->mp->roundLabelDiameter)/(float)2;//mode1计算圆标Y坐标
        textLabelPosY = mode1RoundLabelPosY + ud->mp->bkgPicHeight - (ud->mp->bkgPicHeight-ud->mp->bkgPicRectHeight)/(float)2;//mode1计算站标Y坐标

        if(ud->mp->numsOfStation<=25)
        {
            pageNum = 1;
        }
        else if((25<ud->mp->numsOfStation)&&(ud->mp->numsOfStation<= 50))
        {
            pageNum = 2;
        }
        else
        {
            pageNum = 3;
        }

        if((pageNum==2)&&((ud->mp->numsOfStation%2)!=0))
        {
            ud->mp->numsOfStation++;
            ud->station.append("");
        }
        else
        {

        }

        if((pageNum==3)&&((ud->mp->numsOfStation%3)!=0))
        {
            ud->mp->numsOfStation += (3-ud->mp->numsOfStation%3);
            for(i=0;i<(3-ud->mp->numsOfStation%3);i++)
            {
                ud->station.append("");
            }
        }
        else
        {

        }

    }
    else if(ud->mp->Mode==2)
    {
        mode2RoundLabelPosUpY = ud->mp->containerLabelPosY;//mode2计算圆标上排Y坐标
        mode2RoundLabelPosDownY = ud->mp->containerLabelPosY + ud->mp->bkgPicHeight - ud->mp->roundLabelDiameter;//mode2计算圆标下排Y坐标
        pageNum=1;
    }


    containerLabelStyleSheet = "QLabel{background:transparent;background-image:;}";
    picPath = " url()";//13
    picPath.insert(5,ud->picDir).insert(41,ud->mp->bkgPicName);
    containerLabelStyleSheet.insert(47,picPath);//容器label的样式添加背景图
    //qDebug()<<"containerLabelStyleSheet="<<containerLabelStyleSheet;


    roundLabelBaseStyleSheet = "QLabel{background:transparent;border-radius:;background-color:;font:;}";
    roundLabelBaseStyleSheet.insert(68,ud->mp->roundLabelFontSize);
    roundLabelBaseStyleSheet = roundLabelBaseStyleSheet.insert(44,ud->mp->roundLabelborderRadius);
    roundLabelStyleSheetPassed = roundLabelBaseStyleSheet.insert(66,ud->mp->roundLabelColorPassed);
    roundLabelStyleSheetArrived = roundLabelBaseStyleSheet.remove(66,5).insert(66,ud->mp->roundLabelColorArrived);
    roundLabelStyleSheetNonarrival = roundLabelBaseStyleSheet.remove(66,3).insert(66,ud->mp->roundLabelColorNonarrival);

    textLabelBaseStyleSheet = "QLabel{background:;color:;font:;}";
    textLabelBaseStyleSheet.insert(31,ud->mp->textLabelFontSize);
    textLabelBaseStyleSheet = textLabelBaseStyleSheet.insert(18,ud->mp->textLabelBkg);
    textLabelStyleSheetNonarrival = textLabelBaseStyleSheet.insert(36,ud->mp->textLabelColorNonarrival);
    textLabelStyleSheetPassed = textLabelBaseStyleSheet.remove(36,4).insert(36,ud->mp->textLabelColorPassed);//生成站标样式表

}

void screen::loadMode1()
{
    ui->num->setText(ud->mp->lineNum);//显示线路名
    ui->num->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->line->setText(ud->startToTerminal);//显示始末站
    ui->line->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

    containerLabel = new QLabel(this);
    containerLabel->setGeometry(containerLabelGeometry);
    containerLabel->setStyleSheet(containerLabelStyleSheet);//设置容器标签位置和样式


    if(pageNum==1)//站点数小于等于25
        createModeArrowLabels(ud->mp->numsOfStation);
    else if(pageNum==2)//25<站点数<=50
        createModeArrowLabels(ud->mp->numsOfStation/2);
    else//50<站点数
        createModeArrowLabels(ud->mp->numsOfStation/3);
}

void screen::loadMode2()
{
    ui->num->setText(ud->mp->lineNum);
    ui->num->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->line->setText(ud->startToTerminal);
    ui->line->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

    containerLabel = new QLabel(this);
    containerLabel->setGeometry(containerLabelGeometry);
    containerLabel->setStyleSheet(containerLabelStyleSheet);

    space = ((ud->mp->bkgPicRectWidth-ud->mp->roundLabelDiameter)/(float)(ud->mp->numsOfStation/2-1));

    for(i=0;i<ud->mp->numsOfStation/2;i++)
    {

        mode2RoundLabelsPosX[i] = (ud->mp->bkgPicWidth - ud->mp->bkgPicRectWidth)/2 + i*space;//
        roundLabelGometry[i] = QRect(mode2RoundLabelsPosX[i],mode2RoundLabelPosUpY,ud->mp->roundLabelDiameter,ud->mp->roundLabelDiameter);//
        textLabelPosX[i] = mode2RoundLabelsPosX[i]-(ud->mp->textLabelWidth-ud->mp->roundLabelDiameter)/2;
        textLabelPosY = ud->mp->containerLabelPosY-ud->mp->textLabelHeight;
        textLabelGeometry[i] = QRect(textLabelPosX[i],textLabelPosY,ud->mp->textLabelWidth,ud->mp->textLabelHeight);
        roundLabel[i]=new MyLabel(this);
        roundLabel[i]->setGeometry(roundLabelGometry[i]);
        roundLabel[i]->setNum(i+1);
        roundLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(textTurnGray()));
        //connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(blinkNext()));
        connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(arrivedStationPage()));//XXX站到了

        textLabel[i]=new QLabel(this);
        textLabel[i]->setGeometry(textLabelGeometry[i]);
        textLabel[i]->setStyleSheet(textLabelStyleSheetNonarrival);
        textLabel[i]->setText(ud->station[i]);
        textLabel[i]->setWordWrap(true);
        textLabel[i]->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

    }

    for(i=(ud->mp->numsOfStation/2);i<(ud->mp->numsOfStation);i++)
    {

        mode2RoundLabelsPosX[i] = (ud->mp->bkgPicWidth)-((ud->mp->bkgPicWidth - ud->mp->bkgPicRectWidth)/2)-ud->mp->roundLabelDiameter-((i-ud->mp->numsOfStation/2)*space);
        roundLabelGometry[i] = QRect(mode2RoundLabelsPosX[i],mode2RoundLabelPosDownY,ud->mp->roundLabelDiameter,ud->mp->roundLabelDiameter);
        textLabelPosX[i] = mode2RoundLabelsPosX[i];
        textLabelPosY = ud->mp->containerLabelPosY+ud->mp->bkgPicHeight;
        textLabelGeometry[i] = QRect(mode2RoundLabelsPosX[i],textLabelPosY,ud->mp->textLabelWidth,ud->mp->textLabelHeight);
        roundLabel[i]=new MyLabel(this);
        roundLabel[i]->setGeometry(roundLabelGometry[i]);
        roundLabel[i]->setNum(i+1);
        roundLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(textTurnGray()));
        //connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(blinkNext()));
        connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(arrivedStationPage()));//XXX站到了

        textLabel[i]=new QLabel(this);
        textLabel[i]->setGeometry(textLabelGeometry[i]);
        textLabel[i]->setStyleSheet(textLabelStyleSheetNonarrival);
        textLabel[i]->setText(ud->station[i]);
        textLabel[i]->setWordWrap(true);
        textLabel[i]->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    }

}

void screen::createModeArrowLabels(int num)
{
    space = ((ud->mp->bkgPicRectWidth-ud->mp->roundLabelDiameter)/(float)(num-1));

    for(i=0;i<(num);i++)
    {
        mode1RoundLabelsPosX[i] = i*space;

        roundLabelGometry[i] = QRect(mode1RoundLabelsPosX[i],mode1RoundLabelPosY,ud->mp->roundLabelDiameter,ud->mp->roundLabelDiameter);
        textLabelPosX[i] = mode1RoundLabelsPosX[i] - (ud->mp->textLabelWidth-ud->mp->roundLabelDiameter)/2;
        textLabelGeometry[i] = QRect(textLabelPosX[i],textLabelPosY,ud->mp->textLabelWidth,ud->mp->textLabelHeight);
        //圆标
        roundLabel[i]=new MyLabel(this);
        roundLabel[i]->setGeometry(roundLabelGometry[i]);
        roundLabel[i]->setNum(i+1);

        connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(textTurnGray()));
        //connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(blinkNext()));
        connect(roundLabel[i],SIGNAL(nextStation()),this,SLOT(arrivedStationPage()));//XXX站到了
        //站标
        textLabel[i]=new QLabel(this);
        textLabel[i]->setGeometry(textLabelGeometry[i]);
        textLabel[i]->setStyleSheet(textLabelStyleSheetNonarrival);
        textLabel[i]->setText(ud->station[i]);
        textLabel[i]->setWordWrap(true);
        textLabel[i]->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

    }
    connect(roundLabel[num-1],SIGNAL(nextStation()),this,SLOT(nextPage()));
}
void screen::loadMode3()
{

}

void screen::arrivedStationPage()
{
    arrivedstation *AS = new arrivedstation();
    this->hide();
    AS->setWindowFlags(Qt::FramelessWindowHint);
    AS->move(0,0);
    AS->exec();
    this->show();
}

void screen::nextStationPage(QString text)
{
    nextstation *NS = new nextstation();
    this->hide();
    NS->setWindowFlags(Qt::FramelessWindowHint);
    NS->move(0,0);
    NS->setNextStationLabelText(text);//设置到站文本信息，函数是public以便调用
    qDebug()<<"Display NextStation Page";
    connect(NS,SIGNAL(pageclosed()),this,SLOT(switchStationsPage()));
    NS->exec();
}

void screen::switchStationsPage()
{
    switchstations *SS = new switchstations();
    SS->setWindowFlags(Qt::FramelessWindowHint);
    SS->move(0,0);
    qDebug()<<"Display SwitchStations Page";
    SS->exec();
    this->show();
}
//闪烁下一个
void screen::blinkNext()
{
    if(pageNum==1)//Circle也是一页
    {
        //blinkcount++;//仅模拟闪烁
        if(blinkcount>=ud->mp->numsOfStation)
        {
            return;
        }
        else
        {
            roundLabel[blinkcount]->Blink();
        }
        blinkcount++;
    }
    else if(pageNum==2)
    {
        //blinkcount++;//仅模拟闪烁
        if(blinkcount>=(ud->mp->numsOfStation/2))
        {
            return;
        }
        else
        {
            roundLabel[blinkcount]->Blink();
        }
        blinkcount++;
    }
    else if(pageNum==3)
    {
        //blinkcount++;//仅模拟闪烁
        if(blinkcount>=(ud->mp->numsOfStation/3))
        {
            return;
        }
        else
        {
            roundLabel[blinkcount]->Blink();
        }
        blinkcount++;
    }

}
//过站字体变灰
void screen::textTurnGray()
{
    textLabel[textchangecolorcount]->setStyleSheet(textLabelStyleSheetPassed);
    textchangecolorcount++;
}
//站名跳变到下一页
void screen::nextPage()//只有Arrow模式有
{
    if(pageNum==1)
    {
        return;
    }
    else
    {
        pagecount++;
        if(pagecount==pageNum)
        {
            return;
        }
        else
        {
            qDebug()<<"from "<<pagecount*(ud->mp->numsOfStation/pageNum)<<" to "<<(pagecount+1)*(ud->mp->numsOfStation/pageNum)-1;
            for(i=(pagecount*(ud->mp->numsOfStation/pageNum));i<((pagecount+1)*(ud->mp->numsOfStation/pageNum));i++)
            {
                //圆标变红
                roundLabel[i-pagecount*(ud->mp->numsOfStation/pageNum)]->setNum(i+1);
                roundLabel[i-pagecount*(ud->mp->numsOfStation/pageNum)]->setStyleSheet(roundLabelStyleSheetNonarrival);
                //站名重新加载
                textLabel[i-pagecount*(ud->mp->numsOfStation/pageNum)]->setText(ud->station[i]);
                textLabel[i-pagecount*(ud->mp->numsOfStation/pageNum)]->setStyleSheet(textLabelStyleSheetNonarrival);
            }
            switchcount=0;
            blinkcount=0;
            textchangecolorcount=0;
            //roundLabel[0]->Blink();
        }
    }

}
