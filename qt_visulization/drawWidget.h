#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>

#include <QMouseEvent>

#include <QPainter>
#include <QBrush>

#include "SPGraph/SPGraph.h"
#include "shapes/Helix.h"
#include "shapes/TextInEllipse.h"
#include "qhelix.h"

class drawWidget : public QGraphicsView
{

public:
    drawWidget( QWidget* parent = nullptr );
    void setGraph( std::vector<SPGraph<Shaape*>*>* g );
    QPoint drawRecursive(Node<Shaape*>* start);

    QPoint drawElement(Shaape* sh);
    ~drawWidget();

public slots:
    void drawGraphs();

protected:
    QGraphicsScene *scene;

    std::vector<SPGraph<Shaape*>*>* graphs;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;

    QBrush greenBrush;
    QPen outlinePen;
};

#endif // GLWIDGET_H
