#include "board.h"
#include <iostream>
#include <string>
#include <QGraphicsSceneMouseEvent>

Board::Board(int size, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_size(size), m_tileSize(tileSize)
{
    m_state = State::Stop;
    m_tiles.resize(m_size);

    for (int row=0; row<m_size; row++)
    {
        m_tiles[row].resize(m_size);
    }
    for (int row=0; row<m_size; row++){
        for (int col=0; col<m_size; col++){
            Tile *tile = new Tile(tileSize, this);
            tile->setPos(row*tileSize, col*tileSize);
            m_tiles[row][col] = tile;
        }
    }
}

Board::Board(Board &other)
{
    m_size = other.m_size;
    m_size = other.m_size;
    m_tileSize = other.m_tileSize;
    m_state = other.m_state;

    for (int row=0; row<m_size; row++){
        for (int col=0; col<m_size; col++){
            m_tiles[row][col] = new Tile(*other.m_tiles[row][col]);
        }
    }
}

QRectF Board::boundingRect() const
{
    return QRectF(0, 0, m_size*m_tileSize, m_size*m_tileSize);
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
    for (int row=1; row<m_size-1; row++){
        for (int col=1; col<m_size-1; col++){
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
    if(m_state == State::Stop)
    {
        allowMousePressEventsForAllTiles(true);
        reset();
    }
    else
    {
        allowMousePressEventsForAllTiles(false);
    }
}

void Board::reset()
{
    forEachTile([](Tile* tile){
        tile->activate(false);
        tile->updateActive();
    });
    update();
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



