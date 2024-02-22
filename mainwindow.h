#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QString>
#include <QTimer>
#include "Tile.h"
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // void setTimer(QTimer *newTimer);

private slots:


private:
    // void mousePressEvent(QGraphicsSceneMouseEvent *event);

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Board *board;
    // MySquare *square;
    // QTimer *timer;
 };
#endif // MAINWINDOW_H
