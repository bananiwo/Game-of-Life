#ifndef TILE_H
#define TILE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Tile : public QGraphicsItem
{
public:
    Tile(int tileSize, QGraphicsItem *parent = nullptr);
    Tile(Tile &t);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    inline bool isActive() const {return m_active;}
    inline void activate(bool nextActive) {m_nextActive = nextActive;}
    void changeActive();
    void updateActive();

    void setAllowMousePressEvents(bool allowMousePressEvents);

private:
    int m_tileSize;
    bool m_active;
    bool m_nextActive;
    bool m_allowMousePressEvents = true;
};

#endif // TILE_H
