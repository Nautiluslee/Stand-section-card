#include "arrivedstation.h"
#include "ui_arrivedstation.h"
#include "screen.h"

int arrivedstationcount=0;
extern universdata *ud;

arrivedstation::arrivedstation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arrivedstation)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    styleSheet = "QDialog{background-image:}";
    bkgResource = " url()";
    bkgResource.insert(5,ud->picDir).insert(41,ud->mp->informPageBkg);
    styleSheet.insert(25,bkgResource);
    this->setStyleSheet(styleSheet);

    ui->stationLabel->setText(ud->station[arrivedstationcount].append("，到了"));
    arrivedstationcount++;
    qDebug()<<"Station "<<arrivedstationcount<<"arrived";

    QTimer::singleShot(2000,this, SLOT(Close()));//单次定时器
}

arrivedstation::~arrivedstation()
{
    delete ui;
}

void arrivedstation::Close()
{
    qDebug()<<"ArrivedStations Page Close";
    this->close();
}
