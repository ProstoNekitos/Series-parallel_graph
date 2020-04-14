#include "Shape.h"

void Shaape::rotate(const float &ang) {
    angle = ang;
}

void Shaape::zoom(const float &s) {
    scale = s;
}

void Shaape::move(const Point &p) {
    central = p;
}

void Shaape::paint(const Colour &col) {
    color = col;
}

float Shaape::getRotation() {
    return angle;
}

float Shaape::getScale() {
    return scale;
}

Point Shaape::getCentral() const {
    return central;
}

Colour Shaape::getColor() {
    return color;
}
