#ifndef SPGRAPH_CIRCLE_H
#define SPGRAPH_CIRCLE_H

#include "Shape.h"

class Circle : public virtual Shape {
public:
    explicit Circle(float r = 1, const Point& p = {0,0}) : Shape(p), radius(r){};

    virtual float getRad();
    virtual void setRad(const float& r);

protected:
    float radius;
    void print(std::ostream &o) const override;
};


#endif //SPGRAPH_CIRCLE_H
