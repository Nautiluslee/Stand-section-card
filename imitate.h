#ifndef IMITATE
#define IMITATE
#include <QThread>
#include <QDebug>
#include <QFile>

class imitate : public QThread
{
    Q_OBJECT

public:
    explicit imitate(QObject *parent = 0);

protected:
    void run();

private slots:


private:


signals:
    void NextStation(QString ns);
    void SwitchStation();
    void ArrivedStation();
};

#endif // IMITATE

