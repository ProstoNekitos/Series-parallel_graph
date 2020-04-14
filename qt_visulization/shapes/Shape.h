#ifndef SPGRAPH_ShaapeE_H
#define SPGRAPH_ShaapeE_H

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

class Shaape {
public:
    Shaape(const Shaape& sp) = default;
    explicit Shaape(Point center = Point {0, 0}): central(center) {}
    virtual ~Shaape() = default;

    virtual void rotate(const float& ang);
    virtual void zoom(const float& s);
    virtual void move(const Point& p);
    virtual void paint(const Colour& col);

    virtual float getRotation();
    virtual float getScale();
    virtual Point getCentral() const;
    virtual Colour getColor();

    friend std::ostream &operator<<(std::ostream &os, const Shaape &Shaapee);

protected:
    virtual void print(std::ostream &o) const = 0;

    float angle = 0; //degrees
    float scale = 1;
    Point central;
    Colour color{0,0,0};
};

inline std::ostream &operator<<(std::ostream &os, const Shaape &Shaapee) {
    Shaapee.print(os);
    return os;
}


#endif //SPGRAPH_ShaapeE_H
