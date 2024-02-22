#include "Tile.h"

Tile::Tile(int row, int col, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), row(row), col(col), tileSize(tileSize)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    isPressed = false;
}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, tileSize, tileSize);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(isSelected() ? Qt::darkGray : Qt:: lightGray);
    painter->drawRect(boundingRect());
}

int Tile::getRow() const
{
    return row;
}

int Tile::getCol() const
{
    return col;
}

