#include "Shape.h"

void Shape::rotate(const float &ang) {
    angle = ang;
}

void Shape::zoom(const float &s) {
    scale = s;
}

void Shape::move(const Point &p) {
    central = p;
}

void Shape::paint(const Colour &col) {
    color = col;
}

float Shape::getRotation() {
    return angle;
}

float Shape::getScale() {
    return scale;
}

Point Shape::getCentral() {
    return central;
}

Colour Shape::getColor() {
    return color;
}
