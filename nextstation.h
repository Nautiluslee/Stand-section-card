#ifndef NEXTSTATION_H
#define NEXTSTATION_H
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSettings>
#include <QDebug>

namespace Ui {
class nextstation;
}

class nextstation : public QDialog
{
    Q_OBJECT

public:
    explicit nextstation(QWidget *parent = 0);
    ~nextstation();

public slots:
    void setNextStationLabelText(QString text);//设置到站文本信息，public以便调用

private slots:
    void Close();

private:
    Ui::nextstation *ui;

    QString styleSheet,bkgResource;

signals:
    void pageclosed();
};

#endif // NEXTSTATION_H
