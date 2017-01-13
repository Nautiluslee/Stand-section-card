#include "switchstations.h"
#include "ui_switchstations.h"
#include "screen.h"

extern int switchcount;
extern universdata *ud;

switchstations::switchstations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::switchstations)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    styleSheet = "QDialog{background-image:}";
    bkgResource = " url()";
    bkgResource.insert(5,ud->picDir).insert(41,ud->mp->informPageBkg);
    styleSheet.insert(25,bkgResource);
    this->setStyleSheet(styleSheet);

    switchstationslist.append(ud->switchstations[switchcount].split(","));
    for(int i=0;i<switchstationslist.size();i++)
    {
        stationLabel[i] = new QLabel(this);
        stationLabel[i]->setGeometry(300,150+i*70,900,70);
        stationLabel[i]->setStyleSheet("QLabel{background:transparent;color:black;font:40pt;}");
        stationLabel[i]->setText(switchstationslist[i]);
        stationLabel[i]->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    }
    switchcount++;

    QTimer::singleShot(2000,this, SLOT(Close()));
}

switchstations::~switchstations()
{
    delete ui;
}

void switchstations::Close()
{
    qDebug()<<"SwitchStations Page Close";
    this->close();
}

