#include "nextstation.h"
#include "ui_nextstation.h"
#include "screen.h"

extern universdata *ud;
nextstation::nextstation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nextstation)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    styleSheet = "QDialog{background-image:}";
    bkgResource = " url()";
    bkgResource.insert(5,ud->picDir).insert(41,ud->mp->informPageBkg);
    styleSheet.insert(25,bkgResource);
    this->setStyleSheet(styleSheet);

    QTimer::singleShot(2000,this, SLOT(Close()));
}

nextstation::~nextstation()
{
    delete ui;
}

void nextstation::Close()
{
    qDebug()<<"NextStation Page Close";
    this->close();
    emit pageclosed();
}

void nextstation::setNextStationLabelText(QString text)
{
    ui->stationLabel->setText(text);
}

