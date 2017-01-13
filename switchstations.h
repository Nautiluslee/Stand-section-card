#ifndef SWITCHSTATIONS_H
#define SWITCHSTATIONS_H
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSettings>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>


namespace Ui {
class switchstations;
}

class switchstations : public QDialog
{
    Q_OBJECT

public:
    explicit switchstations(QWidget *parent = 0);
    ~switchstations();

private slots:
    void Close();

private:
    Ui::switchstations *ui;

    QString styleSheet,bkgResource;

    QLabel *stationLabel[10];
    QList<QString>switchstationslist;

};

#endif // SWITCHSTATIONS_H
