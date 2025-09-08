#include <QCoreApplication>
#include <QDebug>
#include"mainwindow.h"
#include <QApplication>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Hello World";
    MainWindow w;

    w.show();
    return QApplication::exec();
}