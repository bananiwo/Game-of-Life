#include "Tile.h"

Tile::Tile(int row, int col, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_row(row), m_col(col), m_tileSize(tileSize)
{
    isPressed = false;
}

Tile::Tile(Tile &t)
{
    m_row = t.m_row;
    m_col = t.m_col;
    isPressed = t.isPressed;
    m_tileSize = t.m_tileSize;
}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, m_tileSize, m_tileSize);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(isPressed ? Qt::darkGray : Qt:: lightGray);
    painter->drawRect(boundingRect());
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    changeState();
    update();
}

void Tile::changeState()
{
    isPressed = !isPressed;
}

bool Tile::operator==(const Tile &other) const
{
    if (m_row == other.m_row && m_col == other.m_col && m_tileSize == other.m_tileSize
        && isPressed == other.isPressed)
        return true;
    else
        return false;
}

bool Tile::operator!=(const Tile &other) const
{
    if (m_row == other.m_row && m_col == other.m_col && m_tileSize == other.m_tileSize
        && isPressed == other.isPressed)
        return false;
    else
        return true;
}

