#include "newGraphDialog.h"

NewGraphDialog::NewGraphDialog()
{
    QVBoxLayout* up = new QVBoxLayout;
    up->addWidget(new QLabel("Make your choise"));
    this->setLayout(up);

        QHBoxLayout* middle = new QHBoxLayout;

            src = new NodeSelWidget;
            trm = new NodeSelWidget;

            QGroupBox* sB = new QGroupBox("Source");
            QGroupBox* tB = new QGroupBox("Terminal");

                QHBoxLayout* sL = new QHBoxLayout;
                QHBoxLayout* tL = new QHBoxLayout;

                sB->setLayout(sL);
                tB->setLayout(tL);

                sL->addWidget(src);
                tL->addWidget(trm);

            middle->addWidget(sB);
            middle->addWidget(tB);

        up->addLayout(middle);

        QDialogButtonBox* bb = new QDialogButtonBox(QDialogButtonBox::Ok
                                             | QDialogButtonBox::Cancel);

        connect(bb, SIGNAL(accepted()), this, SLOT(accept()));
        connect(bb, SIGNAL(rejected()), this, SLOT(reject()));

    up->addWidget(bb);
}

void NewGraphDialog::accept()
{
    res = new SPGraph<Shaape*>(src->parse(), trm->parse());
    done(QDialog::Accepted);
}

void NewGraphDialog::reject()
{
    done(QDialog::Rejected);
}
