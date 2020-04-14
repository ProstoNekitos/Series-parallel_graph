#include "Helix.h"

void Helix::setM(const Point &mp) {
    m = mp;
    radius = static_cast<float>(std::sqrt(std::pow(m.x - central.x, 2) + std::pow(m.y - central.y, 2) ));
}

Point Helix::getM() {
    return m;
}

void Helix::print(std::ostream &o) const {
    o << "Helix with center in " << central.x << ' ' << central.y << "; ray with rad and M " << radius << ' ' << m.x << ' ' << m.y <<std::endl;
}
