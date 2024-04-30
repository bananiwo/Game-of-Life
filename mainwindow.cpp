#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(m_windowSize, m_windowSize);
    // center window
    QPoint centerPoint = QGuiApplication::primaryScreen()->geometry().center();
    QPoint topleftPoint = centerPoint - this->rect().center();
    this->move(topleftPoint);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_board = new Board(10, 50);
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
    if(!m_board || m_board->getState() == State::Play)
        return;

    ui->sizeSlider->setEnabled(false);
    m_board->changeState(State::Play);
    m_timer->start(500);
}

void MainWindow::onStopButtonClicked()
{
    if(!m_board || m_board->getState() == State::Setup)
        return;

    ui->sizeSlider->setEnabled(true);
    m_board->changeState(State::Setup);
    m_timer->stop();
}

void MainWindow::onBoardSizeChanged(int newSize)
{
    // scene->removeItem(m_board);
    int graphicsViewSize = ui->graphicsView->size().height();
    int tileSize = graphicsViewSize / newSize;
    m_board = new Board(newSize, tileSize);
    scene->addItem(m_board);
    update();
}

void MainWindow::advanceTime()
{
    m_board->advance();
}





