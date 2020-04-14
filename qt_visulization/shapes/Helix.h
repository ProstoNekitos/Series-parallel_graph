#ifndef SPGRAPH_HELIX_H
#define SPGRAPH_HELIX_H


#include "Circle.h"
#include <cmath>

class Helix : virtual public Circle {
public:
    Helix(const Point& cent = Point{3,2}, float r = 1, const Point& mp = Point{2,2}) : Circle(r, cent), m(mp) {}

    void setM(const Point& mp);
    Point getM();

protected:
    void print(std::ostream &o) const override;
    Point m;

};


#endif //SPGRAPH_HELIX_H
