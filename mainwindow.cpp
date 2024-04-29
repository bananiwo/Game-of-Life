#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    board = new Board(10, 10, 40);
    scene->addItem(board);
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onPlayButtonClicked()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayButtonClicked()
{
    if(board == nullptr || board->getState() == State::Play)
        return;

    ui->sizeSlider->setEnabled(false);
    board->changeState(State::Play);
}

void MainWindow::onStopButtonClicked()
{
    if(board == nullptr || board->getState() == State::Setup)
        return;

    ui->sizeSlider->setEnabled(true);
    board->changeState(State::Setup);
}





