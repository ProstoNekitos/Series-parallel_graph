#ifndef QHELIX_H
#define QHELIX_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPoint>

#include <QtMath>

#include <shapes/Helix.h>

class QHelix : public QGraphicsItem
{
public:
    QHelix(Helix* h);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                   QWidget *) override;
private:
    void calc();

    float x1;
    float y1;
    float radius;

    QPen pen;

    std::vector<QPoint> points;
    size_t segNum;
};

#endif // QHELIX_H
