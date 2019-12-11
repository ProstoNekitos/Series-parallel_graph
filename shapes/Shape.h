#ifndef SPGRAPH_SHAPE_H
#define SPGRAPH_SHAPE_H

#include <algorithm>
#include <ostream>

struct Colour
{
    short r;
    short g;
    short b;
};

struct Point
{
    float x;
    float y;
};

class Shape {
public:
    Shape(const Shape& sp) = default;
    explicit Shape(Point center = Point {0, 0}): central(center) {}
    virtual ~Shape() = default;

    virtual void rotate(const float& ang);
    virtual void zoom(const float& s);
    virtual void move(const Point& p);
    virtual void paint(const Colour& col);

    virtual float getRotation();
    virtual float getScale();
    virtual Point getCentral();
    virtual Colour getColor();

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

protected:
    virtual void print(std::ostream &o) const = 0;

    float angle = 0; //degrees
    float scale = 1;
    Point central;
    Colour color{0,0,0};
};

inline std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    shape.print(os);
    return os;
}


#endif //SPGRAPH_SHAPE_H
