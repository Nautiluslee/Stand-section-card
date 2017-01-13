#include "screen.h"
#include "universdata.h"
#include <QApplication>
//#include <QWSServer>

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");//图形库路径
    QApplication a(argc, argv);

//    QWSServer::setBackground(QBrush(Qt::NoBrush));

//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
/*
    int fontId = QFontDatabase::addApplicationFont("/usr/lib/fonts/simkai.ttf");
    QString myfont = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(myfont);
    QApplication::setFont(font);
*/
    universdata ud = universdata();//12/19
    screen w;
    //无边框
    w.setWindowFlags(Qt::FramelessWindowHint);
    //显示位置移动到左上角
    w.move(0,0);
    w.show();

    return a.exec();
}
