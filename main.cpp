#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/style/stylesheet.qss");//读取QSS文件中的内容
    if(qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());//把字节流转成字符串
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("Open failed");
    }

    MainWindow w;
    w.show();
    return a.exec();
}
