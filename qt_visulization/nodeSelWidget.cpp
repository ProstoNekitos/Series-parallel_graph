#include "nodeSelWidget.h"

NodeSelWidget::NodeSelWidget(QWidget *parent) : QWidget(parent)
{
    mainLay = new QVBoxLayout(this);
    box = new QComboBox(this);
    box->addItem("Circle");
    box->addItem("Helix");
    box->addItem("Ellipse");
    box->addItem("Text");
    box->addItem("Text in ellipse");

    connect(box, SIGNAL(currentTextChanged(QString)), this, SLOT(update()));

    this->setLayout(mainLay);
    mainLay->addWidget(box);
    params = setParameters();
    mainLay->addWidget(params);
}

QGroupBox *NodeSelWidget::setParameters()
{
    QGroupBox* out = new QGroupBox("Parameters", this);
    QVBoxLayout* l = new QVBoxLayout(out);
    out->setLayout(l);
    l->addWidget(setShaapee());

    if( box->currentText() == "Circle" )
        l->addWidget(setCircle());
    if( box->currentText() == "Helix" )
        l->addWidget(setHelix());
    if( box->currentText() == "Ellipse" )
        l->addWidget(setEllipse());
    if( box->currentText() == "Text" )
        l->addWidget(setText());
    if( box->currentText() == "Text in ellipse" )
        l->addWidget(setTextInEllipse());
    return out;
}

QGroupBox *NodeSelWidget::setShaapee()
{
    QGroupBox* out = new QGroupBox("Shaapee", this);
    QVBoxLayout* l = new QVBoxLayout(out);
    out->setLayout(l);

        QHBoxLayout* hl1 = new QHBoxLayout();
            hl1->addLayout(labelLineEdit("Rotation", "angle", "in degrees"));
            hl1->addLayout(labelLineEdit("Scale", "scale"));
            l->addLayout(hl1);

        QHBoxLayout* hl2 = new QHBoxLayout();
            hl2->addWidget(point("Central", "central"));
            hl2->addWidget(newColorPicker()); //todo
            l->addLayout(hl2);

    return out;
}

QGroupBox *NodeSelWidget::setCircle()
{
    QGroupBox* out = new QGroupBox("Circle");
    out->setLayout(labelLineEdit("Radius", "rad"));
    return out;
}

QGroupBox *NodeSelWidget::setEllipse()
{
    QGroupBox* out = new QGroupBox("Ellipse");
    QVBoxLayout* vl = new QVBoxLayout;
    out->setLayout(vl);

    vl->addWidget(setCircle());
    vl->addLayout(labelLineEdit("Horizontal Radius", "hrad", "the other one is vertical"));

    return out;
}

QGroupBox *NodeSelWidget::setHelix()
{
    QGroupBox* out = new QGroupBox("Helix");
    QVBoxLayout* vl = new QVBoxLayout;
    out->setLayout(vl);

    vl->addWidget(setCircle());
    vl->addWidget(point("M point", "m"));

    return out;
}

QGroupBox *NodeSelWidget::setText()
{
    QGroupBox* out = new QGroupBox("Text");
    QVBoxLayout* vl = new QVBoxLayout;
    out->setLayout(vl);

    vl->addLayout(labelLineEdit("Text:", "text"));

    return out;
}

QGroupBox *NodeSelWidget::setTextInEllipse()
{
    QGroupBox* out = new QGroupBox("Text In Ellipse");
    QVBoxLayout* vl = new QVBoxLayout;
    out->setLayout(vl);

    vl->addWidget(setEllipse());
    vl->addWidget(setText());

    vl->addWidget(point("Shift", "shift"));

    return out;
}

//////

void NodeSelWidget::update()
{
    mainLay->removeWidget(params);
    delete params;
    box->setEnabled(true);
    params = setParameters();
    mainLay->addWidget(params);
}

/////

Shaape *NodeSelWidget::parse()
{
    //Shaapee params
    Point cent{ params->findChild<QLineEdit*>("central_X")->text().toFloat(),
                params->findChild<QLineEdit*>("central_Y")->text().toFloat() };

    float scale = params->findChild<QLineEdit*>("scale")->text().toFloat();
    float angle = params->findChild<QLineEdit*>("angle")->text().toFloat();
    auto* cp = params->findChild<ColorPicker*>("color");
    Colour col{ static_cast<short>(cp->col.red()), static_cast<short>(cp->col.green()),
                static_cast<short>(cp->col.blue())};

    if( box->currentText() == "Circle" )
        res = new Circle( params->findChild<QLineEdit*>("rad")->text().toFloat(),
                          cent );

    if( box->currentText() == "Helix" )
        res = new Helix(cent, params->findChild<QLineEdit*>("rad")->text().toFloat(),
                        Point{params->findChild<QLineEdit*>("m_X")->text().toFloat(),
                        params->findChild<QLineEdit*>("m_Y")->text().toFloat()});

    if( box->currentText() == "Ellipse" )
        res = new Ellipse( cent, params->findChild<QLineEdit*>("rad")->text().toFloat(),
                           params->findChild<QLineEdit*>("hrad")->text().toFloat() );

    if( box->currentText() == "Text" )
        res = new Text(params->findChild<QLineEdit*>("text")->text().toStdString(),
                       cent);

    if( box->currentText() == "Text in ellipse" )
        res = new TextInEllipse(params->findChild<QLineEdit*>("text")->text().toStdString(),
                                cent,
                                Point{params->findChild<QLineEdit*>("shift_X")->text().toFloat(),
                                      params->findChild<QLineEdit*>("shift_Y")->text().toFloat()},
                                params->findChild<QLineEdit*>("rad")->text().toFloat(),
                                params->findChild<QLineEdit*>("hrad")->text().toFloat());

    res->zoom(scale);
    res->rotate(angle);
    res->paint(col);
    res->move(cent);

    return res;
}

void NodeSelWidget::change()
{
    Circle* c = dynamic_cast<Circle*>(res);
    if( c )
        c->setRad(params->findChild<QLineEdit*>("rad")->text().toFloat());

    Helix* h = dynamic_cast<Helix*>(res);
    if( h )
        h->setM(Point{params->findChild<QLineEdit*>("m_X")->text().toFloat(),
                params->findChild<QLineEdit*>("m_Y")->text().toFloat()});

    Ellipse* e = dynamic_cast<Ellipse*>(res);
    if( e )
        e->setHorizontalRadius(params->findChild<QLineEdit*>("hrad")->text().toFloat());

    Text* t = dynamic_cast<Text*>(res);
    if( t )
        t->setText(params->findChild<QLineEdit*>("text")->text().toStdString());

    TextInEllipse* tie = dynamic_cast<TextInEllipse*>(res);
    if( tie )
        tie->setShift(Point{params->findChild<QLineEdit*>("shift_X")->text().toFloat(),
                            params->findChild<QLineEdit*>("shift_Y")->text().toFloat()});
    //for ShaapeE

    auto* cp = params->findChild<ColorPicker*>("color");
    Colour col{ static_cast<short>(cp->col.red()), static_cast<short>(cp->col.green()),
                static_cast<short>(cp->col.blue())};

    res->zoom(params->findChild<QLineEdit*>("scale")->text().toFloat());
    res->move(Point{params->findChild<QLineEdit*>("central_X")->text().toFloat(),
            params->findChild<QLineEdit*>("central_Y")->text().toFloat()});
    res->rotate(params->findChild<QLineEdit*>("angle")->text().toFloat());
    res->paint(col);
}

void NodeSelWidget::display(Shaape* in)
{
    Circle* c = dynamic_cast<Circle*>(in);
    if( c )
    {
        box->setCurrentText("Circle");
        params->findChild<QLineEdit*>("rad")->setText(QString::number(c->getRad()));
    }

    Helix* h = dynamic_cast<Helix*>(in);
    if( h )
    {
        box->setCurrentText("Helix");
        params->findChild<QLineEdit*>("rad")->setText(QString::number(h->getRad()));
        params->findChild<QLineEdit*>("m_X")->setText(QString::number(h->getM().x));
        params->findChild<QLineEdit*>("m_Y")->setText(QString::number(h->getM().y));
    }

    Ellipse* e = dynamic_cast<Ellipse*>(in);
    if( e )
    {
        box->setCurrentText("Ellipse");
        params->findChild<QLineEdit*>("rad")->setText(QString::number(e->getRad()));
        params->findChild<QLineEdit*>("hrad")->setText(QString::number(e->getHorizontalRadius()));
    }

    Text* t = dynamic_cast<Text*>(in);
    if( t )
    {
        box->setCurrentText("Text");
        params->findChild<QLineEdit*>("text")->setText(QString::fromStdString(t->getText()));
    }

    TextInEllipse* tie = dynamic_cast<TextInEllipse*>(in);
    if( tie )
    {
        box->setCurrentText("Text in ellipse");
        params->findChild<QLineEdit*>("text")->setText(QString::fromStdString(tie->getText()));
        params->findChild<QLineEdit*>("rad")->setText(QString::number(tie->getRad()));
        params->findChild<QLineEdit*>("hrad")->setText(QString::number(tie->getHorizontalRadius()));
        params->findChild<QLineEdit*>("shift_X")->setText(QString::number(tie->getShift().x));
        params->findChild<QLineEdit*>("shift_Y")->setText(QString::number(tie->getShift().y));
    }

    //for ShaapeE
    params->findChild<QLineEdit*>("central_X")->setText(QString::number(in->getCentral().x));
    params->findChild<QLineEdit*>("central_Y")->setText(QString::number(in->getCentral().y));
    params->findChild<QLineEdit*>("scale")->setText(QString::number(in->getScale()));
    params->findChild<QLineEdit*>("angle")->setText(QString::number(in->getRotation()));

    params->findChild<ColorPicker*>("color")->setColor(in->getColor().r, in->getColor().g,
                                                       in->getColor().b);

    box->setEnabled(false);

    res = in;

    return;
}


//STAP IT, GET SOME HELP
QHBoxLayout *NodeSelWidget::labelLineEdit(QString label, QString name, QString placeholder)
{
    QHBoxLayout* out = new QHBoxLayout();
    out->addWidget(new QLabel(label));

    auto* iF = new QLineEdit();
    iF->setAccessibleName(name);
    iF->setObjectName(name);
    iF->setPlaceholderText(placeholder);

    out->addWidget(iF);

    return out;
}

QGroupBox *NodeSelWidget::point(QString title, QString name)
{
    QGroupBox* box = new QGroupBox(title);
    QHBoxLayout* hl = new QHBoxLayout;
    box->setLayout(hl);

    QLineEdit* x = new QLineEdit();
    x->setPlaceholderText("X");
    x->setObjectName(name + "_X");

    QLineEdit* y = new QLineEdit();
    y->setPlaceholderText("Y");
    y->setObjectName(name + "_Y");

    hl->addWidget(x);
    hl->addWidget(y);

    return box;
}

ColorPicker *NodeSelWidget::newColorPicker()
{
    ColorPicker* cpl = new ColorPicker;
    cpl->setObjectName("color");
    return cpl;
}
