#include "colorPicker.h"

#include <iostream>

ColorPicker::ColorPicker(QWidget* parent)
    : QLabel(parent) {
    pm = new QPixmap(16, 16);
    pm->fill(Qt::black);
    this->setPixmap(*pm);
}

ColorPicker::~ColorPicker() {
    delete pm;
}

void ColorPicker::setColor(short r, short g, short b)
{
    col = QColor(r, g, b);
    update();
}

void ColorPicker::update()
{
    pm->fill(col);
    this->setPixmap(*pm);
}



void ColorPicker::mousePressEvent(QMouseEvent*) {
    col = QColorDialog::getColor(col, this, "Pen colour");
    update();
}
