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
    inline int getRow() const {return m_row;}
    inline int getCol() const {return m_col;}
    void changeState();
    bool isPressed;
    bool operator==(const Tile &other) const;
    bool operator!=(const Tile &other) const;
private:
    int m_row;
    int m_col;
    int m_tileSize;
};

#endif // TILE_H
