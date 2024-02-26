#ifndef TILE_H
#define TILE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Tile : public QGraphicsItem
{
public:
    Tile(int row, int col, int tileSize, QGraphicsItem *parent = nullptr);
    Tile(Tile &t);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    int getRow() const;
    int getCol() const;
    void changeState();
    bool isPressed;
    bool operator==(const Tile &other) const;
    bool operator!=(const Tile &other) const;
private:
    int row;
    int col;
    int tileSize;
};

#endif // TILE_H
