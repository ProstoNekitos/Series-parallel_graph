#ifndef NODESELECTION_H
#define NODESELECTION_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>

#include <shapes/TextInEllipse.h>
#include "shapes/Helix.h"

#include "colorPicker.h"

class NodeSelWidget : public QWidget
{
    Q_OBJECT
public:
    QComboBox* box;
    QGroupBox* params;
    QVBoxLayout* mainLay;
    Shaape* res;

private:
    QGroupBox* setParameters();
    QGroupBox* setShaapee();
    QGroupBox* setCircle();
    QGroupBox* setEllipse();
    QGroupBox* setHelix();
    QGroupBox* setText();
    QGroupBox* setTextInEllipse();

private:
    QHBoxLayout* labelLineEdit(QString label, QString name, QString placeholder = "");
    QGroupBox* point(QString title, QString name);
    ColorPicker* newColorPicker();

private slots:
    void update();

public:
    Shaape* parse();
    void change();
    void display(Shaape* in);

    explicit NodeSelWidget(QWidget *parent = nullptr);


};
#endif // NODESELECTION_H
