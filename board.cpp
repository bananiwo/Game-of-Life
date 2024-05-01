#include "board.h"
#include <iostream>
#include <string>
#include <QGraphicsSceneMouseEvent>

Board::Board(int gridNum, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_gridNum(gridNum), m_tileSize(tileSize)
{
    m_state = State::Stop;
    m_tiles.resize(m_gridNum);

    for (int row=0; row<m_gridNum; row++)
    {
        m_tiles[row].resize(m_gridNum);
    }
    for (int row=0; row<m_gridNum; row++){
        for (int col=0; col<m_gridNum; col++){
            Tile *tile = new Tile(tileSize, this);
            tile->setPos(row*tileSize, col*tileSize);
            m_tiles[row][col] = tile;
        }
    }
}

Board::Board(Board &other)
{
    m_gridNum = other.m_gridNum;
    m_gridNum = other.m_gridNum;
    m_tileSize = other.m_tileSize;
    m_state = other.m_state;

    for (int row=0; row<m_gridNum; row++){
        for (int col=0; col<m_gridNum; col++){
            m_tiles[row][col] = new Tile(*other.m_tiles[row][col]);
        }
    }
}

QRectF Board::boundingRect() const
{
    int offset = 10;
    return QRectF(-offset, -offset, m_gridNum*m_tileSize+2*offset, m_gridNum*m_tileSize+2*offset);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
 // Draw border
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::darkGray);
    painter->drawRect(boundingRect());
}

void Board::advance()
{
    if(m_state != State::Play) return;
    // next move logic
    for (int row=0; row<m_gridNum; row++){
        for (int col=0; col<m_gridNum; col++){
            Tile* currentTile = m_tiles[row][col];
            int activeNeighbours = 0;
            QVector<Tile*> n = getNeighbours(row, col);
            for (Tile* neighbour : n){
                if (neighbour->isActive()) activeNeighbours++;
            }
            if(currentTile->isActive())
            {
                if((activeNeighbours < 2) || (activeNeighbours > 3))
                {
                    currentTile->activate(false);
                }
            }
            else
            {
                if(activeNeighbours == 3)
                {
                    currentTile->activate(true);
                }
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
    QVector<Tile*> neighbours{};
    for (int i=-1; i<=1; i++)
    {
        for (int j=-1; j<=1; j++)
        {
            if (i==0 && j==0) continue;
            int newRow = (row+i + m_gridNum) % m_gridNum;
            int newCol = (col+j + m_gridNum) % m_gridNum;
            // check if the neighboring cell is within the grid bounds
            if (newRow >= 0 && newRow < m_gridNum && newCol >= 0 && newCol < m_gridNum){
                neighbours.append(m_tiles[newRow][newCol]);
            }
        }
    }
    return neighbours;
}



