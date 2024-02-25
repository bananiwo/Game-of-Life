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

Board::Board(Board &other)
{
    rows = other.rows;
    cols = other.cols;
    tileSize = other.tileSize;

    for (Tile *originalTile : other.tiles) {
        Tile *copiedTile = new Tile(*originalTile);
        tiles.append(copiedTile);
    }
}

QRectF Board::boundingRect() const
{
    return QRectF(-10, -10, cols*tileSize+20, rows*tileSize+20);
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

void Board::advance(int phase)
{
    if (!phase) return;

    int pressed = 0;
    for (auto t : tiles) {
        if (t->isPressed) pressed++;
    }

    qDebug() << QString("%1 tiles pressed").arg(pressed);


}
