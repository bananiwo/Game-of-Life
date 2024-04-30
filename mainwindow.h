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


private slots:
    void onPlayButtonClicked();
    void onPauseButtonClicked();
    void onBoardSizeChanged(int newSize);
    void advanceTime();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Board *m_board;
    QTimer *m_timer;
    int m_windowSize = 800;
    int m_timeInterval = 500;
 };
#endif // MAINWINDOW_H
