#ifndef MYLABEL_H
#define MYLABEL_H
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QTextStream>

class MyLabel: public QLabel
{
    Q_OBJECT

public:
    MyLabel(QWidget * parent = 0);


private:
    QTimer *tm;
    QSettings *config;

    QString defaultStyleSheet;
    QString passedStyleSheet;
    QString arrivedStyleSheet;
    QString nonarrivalStyleSheet;

public slots:
    void configParam();
    void Blink();
    void toBlink();

protected:

signals:
    void nextStation();
};

#endif // MYLABEL_H
