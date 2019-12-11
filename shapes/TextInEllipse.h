#ifndef SPGRAPH_TEXTINELLIPSE_H
#define SPGRAPH_TEXTINELLIPSE_H

#include "Text.h"
#include "Ellipse.h"

class TextInEllipse : public virtual Text, public Ellipse{
public:
    TextInEllipse(std::string text, const Point& c = Point{0, 0}, float vr = 4, float hr = 3) : Text(text), Ellipse(c, vr, hr)  {}

    void setShift( const Point& sh );
    Point getShift();


private:
    Point textShift {0,0};
    void print(std::ostream &o) const override;
};


#endif //SPGRAPH_TEXTINELLIPSE_H
