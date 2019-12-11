#ifndef SPGRAPH_ELLIPSE_H
#define SPGRAPH_ELLIPSE_H


#include "Circle.h"

class Ellipse : virtual public Circle {
public:
    Ellipse(const Point& cent = {0,0}, float r = 1, float rh = 1) : Circle(r, cent), rHor(rh){}
    float getHorizontalRadius();
    void setHorizontalRadius(const float& rh);

protected:
    float rHor;
    void print(std::ostream &o) const override;
};


#endif //SPGRAPH_ELLIPSE_H
