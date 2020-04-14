#include "TextInEllipse.h"

void TextInEllipse::setShift(const Point &sh) {
    textShift = sh;
}

Point TextInEllipse::getShift() {
    return textShift;
}

void TextInEllipse::print(std::ostream &o) const {
    o << "Text: " << text << " In an ellipse with coord: " << central.x << ' ' << central.y << " Vrad and Hrad: " << radius << ' ' << rHor << std::endl;
}
