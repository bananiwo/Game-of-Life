#include "board.h"
#include <iostream>
#include <string>
#include <QGraphicsSceneMouseEvent>

Board::Board(int rows, int cols, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_rows(rows), m_cols(cols), m_tileSize(tileSize)
{
    m_state = State::Setup;
    m_tiles.resize(m_rows);

    for (int row=0; row<m_rows; row++)
    {
        m_tiles[row].resize(m_cols);
    }
    for (int row=0; row<rows; row++){
        for (int col=0; col<cols; col++){
            Tile *tile = new Tile(tileSize, this);
            tile->setPos(row*tileSize, col*tileSize);
            m_tiles[row][col] = tile;
        }
    }
}

Board::Board(Board &other)
{
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_tileSize = other.m_tileSize;
    m_state = other.m_state;

    for (int row=0; row<m_rows; row++){
        for (int col=0; col<m_cols; col++){
            m_tiles[row][col] = new Tile(*other.m_tiles[row][col]);
        }
    }
}

QRectF Board::boundingRect() const
{
    return QRectF(-10, -10, m_cols*m_tileSize+20, m_rows*m_tileSize+20);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
 // Draw border
    QPen pen;
    pen.setStyle(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(Qt::darkYellow);
    painter->drawRect(boundingRect());
}

void Board::advance()
{
    if(m_state != State::Play) return;
    // next move logic
    for (int row=1; row<m_rows-1; row++){
        for (int col=1; col<m_cols-1; col++){
            Tile* currentTile = m_tiles[row][col];
            int activeNeighbours = 0;
            QVector<Tile*> n = getNeighbours(row, col);
            for (Tile* neighbour : n){
                if (neighbour->isActive()) activeNeighbours++;
            }
            if(currentTile->isActive() && activeNeighbours < 2)
            {
                currentTile->activate(false);
            }
            if(currentTile->isActive() && activeNeighbours > 3)
            {
                currentTile->activate(false);
            }
            if(!currentTile->isActive() && activeNeighbours == 3)
            {
                currentTile->activate(true);
            }
        }
    }

    forEachTile([](Tile* tile){
        tile->updateActive();
    });

    update();
}

void Board::changeState(const State newState)
{
    m_state = newState;
    if(m_state == State::Play)
    {
        allowMousePressEventsForAllTiles(false);
    }
    else if(m_state == State::Setup)
    {
        allowMousePressEventsForAllTiles(true);
    }
}

void Board::forEachTile(const std::function<void (Tile *)> &func)
{
    for(const auto& row : m_tiles){
        for (Tile* tile : row){
            func(tile);
        }
    }
}

void Board::allowMousePressEventsForAllTiles(bool allow)
{
    forEachTile([allow](Tile* tile){
        tile->setAllowMousePressEvents(allow);
    });
}

QVector<Tile*> Board::getNeighbours(const int row, const int col) const
{
    QVector<Tile*> neighbours;
    neighbours.resize(8);
    neighbours[0] = m_tiles[row-1][col-1];
    neighbours[1] = m_tiles[row-1][col];
    neighbours[2] = m_tiles[row-1][col+1];
    neighbours[3] = m_tiles[row][col-1];
    neighbours[4] = m_tiles[row][col+1];
    neighbours[5] = m_tiles[row+1][col-1];
    neighbours[6] = m_tiles[row+1][col];
    neighbours[7] = m_tiles[row+1][col+1];
    return neighbours;
}



