#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    m_board = new Board(10, 10, 40);
    scene->addItem(m_board);
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onPlayButtonClicked()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
    connect(ui->sizeSlider, SIGNAL(valueChanged(int)), this, SLOT(onBoardSizeChanged(int)));
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(advanceTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayButtonClicked()
{
    if(m_board == nullptr || m_board->getState() == State::Play)
        return;

    ui->sizeSlider->setEnabled(false);
    m_board->changeState(State::Play);
    m_timer->start(500);
}

void MainWindow::onStopButtonClicked()
{
    if(m_board == nullptr || m_board->getState() == State::Setup)
        return;

    ui->sizeSlider->setEnabled(true);
    m_board->changeState(State::Setup);
    m_timer->stop();
}

void MainWindow::onBoardSizeChanged(int newSize)
{
    qDebug() << "New size " << newSize;
}

void MainWindow::advanceTime()
{
    m_board->advance();
}





