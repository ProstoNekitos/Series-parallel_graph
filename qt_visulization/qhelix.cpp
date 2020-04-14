#include "qhelix.h"

QHelix::QHelix(Helix* h) : x1( h->getCentral().x ), y1( h->getCentral().y ),
    radius( h->getRad() ), pen( QColor(h->getColor().r, h->getColor().g, h->getColor().b) ),
    segNum( h->getScale() )
{
    this->setRotation(h->getRotation());
    calc();
}

QRectF QHelix::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}

void QHelix::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(pen);
    painter->drawPolyline(points.data(), points.size());
}

void QHelix::calc()
{
    float piMultiplier = M_PI;
    for (size_t i = 0; i < segNum; ++i)
        {
            //float theta = i / segNum*piMultiplier;
            float x = x1 + (radius * cos(i*piMultiplier/segNum));
            float y = y1 + (radius * sin(i*piMultiplier/segNum));

            points.emplace_back(QPoint{x, y});

            radius += 1;
        }
}
