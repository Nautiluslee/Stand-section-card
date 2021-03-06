#ifndef SCREEN_H
#define SCREEN_H
#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <QLabel>
#include <QFontDatabase>
#include <QTextCodec>
#include <QTextStream>
#include <QSettings>
#include <QFile>
#include <QStringList>
#include "mylabel.h"
#include "imitate.h"
#include "arrivedstation.h"
#include "nextstation.h"
#include "switchstations.h"
#include "universdata.h"

#include "ipc_usocket.h"

namespace Ui {
class screen;
}

class screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit screen(QWidget *parent = 0);
    ~screen();

private slots:
    void configParam();
    void loadMode1();
    void loadMode2();
    void loadMode3();
    void createModeArrowLabels(int num);
    void arrivedStationPage();
    void nextStationPage(QString text);
    void switchStationsPage();
    void blinkNext();//闪烁下一个
    void textTurnGray();//过站字体变灰
    void nextPage();//站名跳变到下一页

private:
    Ui::screen *ui;

    MyLabel *roundLabel[100];//圆标
    QLabel *textLabel[100];//站标

    float space,mode1RoundLabelsPosX[100],mode1RoundLabelPosY;
    float mode2RoundLabelsPosX[100],mode2RoundLabelPosUpY,mode2RoundLabelPosDownY;//(圆标+空)的宽度,箭头模式圆标站标Y坐标,环形模式圆标站标X坐标
    float textLabelPosX[100],textLabelPosY;
    int pageNum;//mode1站点页数
    int roundLabelRadius;//圆标边弧度
    QLabel *containerLabel;//
    int containerLabelX,containerLabelY,containerLabelWidth,containerLabelHeight;
    QRect containerLabelGeometry;
    QRect roundLabelGometry[100];
    QRect textLabelGeometry[100];
    QString containerLabelStyleSheet;
    QString roundLabelBaseStyleSheet,roundLabelStyleSheetPassed,roundLabelStyleSheetArrived,roundLabelStyleSheetNonarrival;
    QString textLabelBaseStyleSheet,textLabelStyleSheetPassed,textLabelStyleSheetNonarrival;
    QString picPath;

    IPC_USOCKSet IPCUSock;



};

#endif // SCREEN_H
