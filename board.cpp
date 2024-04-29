#include "board.h"
#include <iostream>
#include <string>

Board::Board(int rows, int cols, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_rows(rows), m_cols(cols), m_tileSize(tileSize)
{
    m_state = State::Setup;
    for (int row=0; row<rows; row++){
        for (int col=0; col<cols; col++){
            Tile *tile = new Tile(row, col, tileSize, this);
            tile->setPos(col*tileSize, row*tileSize);
            m_tiles.append(tile);
        }
    }
}

Board::Board(Board &other)
{
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_tileSize = other.m_tileSize;
    m_state = other.m_state;

    for (Tile *originalTile : other.m_tiles) {
        Tile *copiedTile = new Tile(*originalTile);
        m_tiles.append(copiedTile);
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
    qDebug() << Q_FUNC_INFO;
}

void Board::changeState(const State newState)
{
    m_state = newState;
    qDebug() << Q_FUNC_INFO << " State = " << newState;
}

bool Board::operator==(const Board &other) const
{
    if (m_rows != other.m_rows || m_cols != other.m_cols || m_tileSize != other.m_tileSize)
        return false;

    for (int i=0; i<m_tiles.length(); i++) {
        if(*m_tiles.at(i) != *other.m_tiles.at(i))
            return false;
    }

    return true;
}

