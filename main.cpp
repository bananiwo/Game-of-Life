#include "mainwindow.h"
#include "TestTile.h"

#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    TestTile testTile;
    QTest::qExec(&testTile, argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("myApp");
    return a.exec();
}
