#include "mainwindow.h"
#include "TestTile.h"
#include "TestBoard.h"

#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    {
    TestTile testTile;
        QTest::qExec(&testTile, argc, argv);}
    {TestBoard testBoard;
        QTest::qExec(&testBoard, argc, argv);}

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("myApp");
    return a.exec();
}
