#ifndef TILE_H
#define TILE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Tile : public QGraphicsItem
{
public:
    Tile(int row, int col, int tileSize, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    int getRow() const;
    int getCol() const;

private:
    int row;
    int col;
    int tileSize;
    bool isPressed;
};

#endif // TILE_H
