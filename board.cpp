#include "board.h"
#include <iostream>
#include <string>

Board::Board(int rows, int cols, int tileSize, QGraphicsItem *parent)
    : QGraphicsItem(parent), rows(rows), cols(cols), tileSize(tileSize)
{
    for (int row=0; row<rows; row++){
        for (int col=0; col<cols; col++){
            Tile *tile = new Tile(row, col, tileSize, this);
            tile->setPos(col*tileSize, row*tileSize);
            tiles.append(tile);
        }
    }
}

QRectF Board::boundingRect() const
{
    return QRectF(-10, -10, cols*tileSize+20, rows*tileSize+20);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setStyle(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(Qt::darkYellow);
    painter->drawRect(boundingRect());
}
