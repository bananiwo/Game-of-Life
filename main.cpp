#include "mainwindow.h"

#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Game of Life");
    // setup icon
    QByteArray base64IconData = "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";
    QByteArray iconData = QByteArray::fromBase64(base64IconData);
    QPixmap iconPixmap;
    iconPixmap.loadFromData(iconData);
    QIcon icon;
    icon.addPixmap(iconPixmap);
    w.setWindowIcon(icon);

    return a.exec();
}
