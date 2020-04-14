#include "Ellipse.h"

float Ellipse::getHorizontalRadius() {
    return rHor;
}

void Ellipse::setHorizontalRadius(const float &rh) {
    rHor = rh;
}

void Ellipse::print(std::ostream &o) const {
    o << "Ellipse with central in " << central.x << ' ' << central.y << " Hrad and Vrad " << rHor << ' ' << radius << std::endl;
}
