#include "Tile.h"

Tile::Tile(int row, int col, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), row(row), col(col), tileSize(tileSize)
{
    isPressed = false;
}

Tile::Tile(Tile &t)
{
    row = t.row;
    col = t.col;
    isPressed = t.isPressed;
    tileSize = t.tileSize;
}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, tileSize, tileSize);
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

int Tile::getRow() const
{
    return row;
}

int Tile::getCol() const
{
    return col;
}

void Tile::changeState()
{
    isPressed = !isPressed;
}

