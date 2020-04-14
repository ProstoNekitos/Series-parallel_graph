#ifndef NEWNODEDIALOG_H
#define NEWNODEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

#include "nodeSelWidget.h"
#include "SPGraph/SPGraph.h"

class NewGraphDialog : public QDialog
{
public:
    NewGraphDialog();

    NodeSelWidget* src;
    NodeSelWidget* trm;

    SPGraph<Shaape*>* res;

public slots:
    void accept();
    void reject();
};

#endif // NEWNODEDIALOG_H
