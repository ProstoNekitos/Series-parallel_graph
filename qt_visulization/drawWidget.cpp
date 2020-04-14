#include "drawWidget.h"

drawWidget::drawWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);

    this->setScene(scene);

    greenBrush.setColor(Qt::green);
    outlinePen.setColor(Qt::black);
    outlinePen.setWidth(2);
}

void drawWidget::setGraph(std::vector<SPGraph<Shaape *> *> *g)
{
    graphs = g;
}

QPoint drawWidget::drawElement(Shaape *in)
{
    float x;
    float y;
    Circle* c = dynamic_cast<Circle*>(in);
    if( c && !dynamic_cast<Helix*>(in) && !dynamic_cast<Ellipse*>(in) )
    {
        QGraphicsEllipseItem* e = new QGraphicsEllipseItem(c->getCentral().x, c->getCentral().y, c->getRad(), c->getRad() );
            e->setPen(QColor(c->getColor().r, c->getColor().g, c->getColor().b));
            //e->setScale(c->getScale());
        scene->addItem(e);

        x = e->x();
        y = e->y();
    }

    Helix* h = dynamic_cast<Helix*>(in);
    if( h )
    {
        QHelix* hel = new QHelix(h);
        scene->addItem(hel);

        x = hel->x();
        y = hel->y();
    }

    TextInEllipse* tie = dynamic_cast<TextInEllipse*>(in);
    if( tie )
    {
        QGraphicsItemGroup* g = new QGraphicsItemGroup;
            QGraphicsTextItem* i = new QGraphicsTextItem(QString::fromStdString(tie->getText()));
                i->setDefaultTextColor(QColor(tie->getColor().r, tie->getColor().g, tie->getColor().b));
                i->setPos(tie->getCentral().x + tie->getShift().x, tie->getCentral().y + tie->getShift().y);
            g->addToGroup(i);

            QGraphicsEllipseItem* e = new QGraphicsEllipseItem(tie->getCentral().x, tie->getCentral().y, tie->getRad(), tie->getHorizontalRadius());
                e->setPen(QColor(tie->getColor().r, tie->getColor().g, tie->getColor().b));
            g->addToGroup(e);
            g->setRotation(tie->getRotation());
            //g->setScale(tie->getScale());

        scene->addItem(g);

        x = g->x();
        y = g->y();
    }
    else
    {
        Ellipse* e = dynamic_cast<Ellipse*>(in);
        if( e )
        {
            QGraphicsEllipseItem* ei = new QGraphicsEllipseItem(e->getCentral().x, e->getCentral().y, e->getRad(), e->getHorizontalRadius());
                ei->setRotation(e->getRotation());
                //ei->setScale(e->getScale());
                ei->setPen(QColor(e->getColor().r, e->getColor().g, e->getColor().b));
            scene->addItem(ei);

            x = ei->x();
            y = ei->y();
        }

        Text* t = dynamic_cast<Text*>(in);
        if( t )
        {
            QGraphicsTextItem* i = new QGraphicsTextItem(QString::fromStdString(t->getText()));
                i->setPos(t->getCentral().x, t->getCentral().y);
                i->setRotation(t->getRotation());
                //i->setScale(t->getScale());
                i->setDefaultTextColor(QColor(t->getColor().r, t->getColor().g, t->getColor().b));
            scene->addItem(i);

            x = i->x();
            y = i->y();
        }
    }
    return QPoint(in->getCentral().x * 1.25, in->getCentral().y * 1.25);
}

QPoint drawWidget::drawRecursive(Node<Shaape *> *start)
{
    QPoint startP = drawElement(*start->data);
    QPoint end;
    for( size_t i = 0; i < start->childs.size(); ++ i )
    {
        end = drawRecursive(start->childs[i]);

        QGraphicsLineItem* l = new QGraphicsLineItem( QLine( startP, end) );

        l->setPen(outlinePen);
        scene->addItem(l);
    }
    return startP;
}

void drawWidget::drawGraphs()
{
    scene->clear();
    for( SPGraph<Shaape*>* gr : *graphs )
    {
        std::vector<Node<Shaape*>*> v;
        gr->depthFirstDecompose(gr->begin().node, v);
        drawRecursive(v.front());
    }
}

drawWidget::~drawWidget(){}
