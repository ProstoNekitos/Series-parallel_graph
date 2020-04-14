#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QColorDialog>

class ColorPicker : public QLabel {
    Q_OBJECT

public:
    explicit ColorPicker(QWidget* parent = Q_NULLPTR); 
    ~ColorPicker();

    void setColor(short r, short g, short b);
    void update();

signals:
    void clicked();

public:
    void mousePressEvent(QMouseEvent* event);
    QColor col = Qt::black;
    QPixmap* pm;
};

#endif // CLICKABLELABEL_H
