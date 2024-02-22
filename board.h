#ifndef BOARD_H
#define BOARD_H

#include <QPainter>
#include <QGraphicsItem>
#include <QVector>
#include "Tile.h"

class Board : public QGraphicsItem
{
public:
    Board(int rows, int cols, int tileSize, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QList<Tile*> tiles;
    int rows;
    int cols;
    int tileSize;
};

#endif // BOARD_H
