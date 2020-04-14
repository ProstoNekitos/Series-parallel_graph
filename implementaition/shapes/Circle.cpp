#include "Circle.h"

float Circle::getRad() {
    return this->radius;
}

void Circle::setRad(const float& r) {
    this->radius = r;
}

void Circle::print(std::ostream &o) const {
    o << "Circle with center in: " << central.x << ' ' << central.y << " and radius of " << radius << std::endl;
}
