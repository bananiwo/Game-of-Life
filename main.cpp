#include "mainwindow.h"

#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Game of Life");
    return a.exec();
}
