#ifndef SPGRAPH_TEXT_H
#define SPGRAPH_TEXT_H

#include <string>
#include "Shape.h"

class Text : virtual public Shaape{

public:
    explicit Text(const std::string& s, const Point& p = Point() ) : Shaape(p), text(s){}

    std::string getText();
    size_t size();

    void setText(const std::string& txt);


protected:
    std::string text;
    void print(std::ostream &o) const override;
};


#endif //SPGRAPH_TEXT_H
