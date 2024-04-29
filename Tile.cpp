#include "Tile.h"

Tile::Tile(int row, int col, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_row(row), m_col(col), m_tileSize(tileSize)
{
    m_active = false;
    m_nextActive = m_active;
}

Tile::Tile(Tile &t)
{
    m_row = t.m_row;
    m_col = t.m_col;
    m_active = t.m_active;
    m_nextActive = m_active;
    m_tileSize = t.m_tileSize;
}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, m_tileSize, m_tileSize);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(m_active ? Qt::darkGray : Qt:: lightGray);
    painter->drawRect(boundingRect());
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_allowMousePressEvents) return;
    changeActive();
    updateActive();
    update();
}

void Tile::changeActive()
{
    m_nextActive = !m_active;
}

void Tile::updateActive()
{
    m_active = m_nextActive;
}

bool Tile::operator==(const Tile &other) const
{
    if (m_row == other.m_row && m_col == other.m_col && m_tileSize == other.m_tileSize
        && m_active == other.m_active)
        return true;
    else
        return false;
}

bool Tile::operator!=(const Tile &other) const
{
    if (m_row == other.m_row && m_col == other.m_col && m_tileSize == other.m_tileSize
        && m_active == other.m_active)
        return false;
    else
        return true;
}

void Tile::setAllowMousePressEvents(bool allowMousePressEvents)
{
    m_allowMousePressEvents = allowMousePressEvents;
}

