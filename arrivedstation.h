#ifndef ARRIVEDSTATION_H
#define ARRIVEDSTATION_H
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QRect>
#include <QSettings>

namespace Ui {
class arrivedstation;
}

class arrivedstation : public QDialog
{
    Q_OBJECT

public:
    explicit arrivedstation(QWidget *parent = 0);
    ~arrivedstation();

private slots:
    void Close();

private:
    Ui::arrivedstation *ui;

    QString styleSheet,bkgResource;

};
#endif // ARRIVEDSTATION_H
