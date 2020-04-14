#ifndef SPGRAPH_TEXTINELLIPSE_H
#define SPGRAPH_TEXTINELLIPSE_H

#include "Text.h"
#include "Ellipse.h"

class TextInEllipse : public virtual Text, public Ellipse{
public:
    TextInEllipse(std::string text = "text", const Point& c = Point{0, 0}, const Point& sh = Point{0,0}, float vr = 1, float hr = 1) : Text(text), Ellipse(c, vr, hr), textShift(sh)  {}

    void setShift( const Point& sh );
    Point getShift();


private:
    Point textShift {0,0};
    void print(std::ostream &o) const override;
};


#endif //SPGRAPH_TEXTINELLIPSE_H
