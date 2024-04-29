#include "Tile.h"

Tile::Tile(int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_tileSize(tileSize)
{
    m_active = false;
    m_nextActive = m_active;
}

Tile::Tile(Tile &t)
{
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

void Tile::setAllowMousePressEvents(bool allowMousePressEvents)
{
    m_allowMousePressEvents = allowMousePressEvents;
}

