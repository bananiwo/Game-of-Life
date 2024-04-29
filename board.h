#ifndef BOARD_H
#define BOARD_H

#include <QPainter>
#include <QGraphicsItem>
#include <QVector>
#include "Tile.h"

enum State
{
    Setup = 0,
    Play = 1
};

class Board : public QGraphicsItem
{
public:
    Board(int rows, int cols, int tileSize, QGraphicsItem *parent = nullptr);
    Board(Board &other);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance();
    void changeState(const State newState);
    inline State getState() const {return m_state;}

private:
    QList<Tile*> m_tiles;
    int m_rows;
    int m_cols;
    int m_tileSize;
    State m_state;
};

#endif // BOARD_H
