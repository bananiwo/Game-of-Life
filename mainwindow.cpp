#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int screenHeight = QGuiApplication::primaryScreen()->size().height();
    int windowHeight = (screenHeight > 900 ? 770 : 570);
    this->setFixedSize(windowHeight, windowHeight);
    m_graphicsViewSize = windowHeight - 50;
    // center window to screen
    int screenCenterX = QGuiApplication::primaryScreen()->geometry().center().x();
    int offsetX = screenCenterX - this->rect().center().x();
    this->move(QPoint(offsetX, 0));

    scene = new QGraphicsScene(this);
    m_timer = new QTimer(this);

    ui->pauseButton->setEnabled(false);
    ui->graphicsView->setFixedSize(m_graphicsViewSize, m_graphicsViewSize);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onPlayButtonClicked()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(onPauseButtonClicked()));
    connect(ui->sizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setupBoard(int)));
    connect(ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(setTimeInterval(int)));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(advanceTime()));

    setupBoard(ui->sizeSlider->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayButtonClicked()
{
    if(!m_board) return;
    if(m_board->getState() == State::Stop)
    {
        ui->startButton->setText("Stop");
        ui->sizeSlider->setEnabled(false);
        ui->pauseButton->setEnabled(true);
        m_board->changeState(State::Play);
        m_timer->start(m_timeInterval);
    }
    else if(m_board->getState() != State::Stop)
    {
        ui->startButton->setText("Start");
        ui->sizeSlider->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        m_board->changeState(State::Stop);
        m_timer->stop();
    }
}

void MainWindow::onPauseButtonClicked()
{
    if(!m_board || m_board->getState() == State::Stop)
        return;
    if (m_board->getState() == State::Paused)
    {
        ui->pauseButton->setText("Pause");
        m_board->changeState(State::Play);
        m_timer->start(m_timeInterval);
    }
    else if(m_board->getState() == State::Play)
    {
        ui->pauseButton->setText("Continue");
        m_board->changeState(State::Paused);
        m_timer->stop();
    }
}

void MainWindow::setupBoard(int sliderValue)
{
    if(m_board){
        scene->removeItem(m_board);
    }
    int gridSize = m_graphicsViewSize - 20;
    QVector<int> divizors {10, 20, 50, 100};
    ui->sizeSlider->setMaximum(divizors.size()-1);
    int tilesNum = divizors[sliderValue];
    int tileSize = gridSize/tilesNum;
    m_board = new Board(tilesNum, tileSize);
    scene->addItem(m_board);
    update();
}

void MainWindow::advanceTime()
{
    m_board->advance();
}

void MainWindow::setTimeInterval(int interval)
{
    m_timeInterval = interval;
    m_timer->setInterval(m_timeInterval);
}
