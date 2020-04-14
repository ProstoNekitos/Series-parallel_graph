#ifndef SPGRAPH_HELIX_H
#define SPGRAPH_HELIX_H


#include "Circle.h"
#include <cmath>

class Helix : virtual public Circle {
public:
    Helix(const Point& cent, float r, const Point& mp) : Circle(r, cent), m(mp) {}

    void setM(const Point& mp);
    Point getM();

protected:
    void print(std::ostream &o) const override;
    Point m;

};


#endif //SPGRAPH_HELIX_H
