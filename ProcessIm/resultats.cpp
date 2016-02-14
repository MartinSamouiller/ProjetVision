#include "resultats.h"
#include "ui_resultats.h"

Resultats::Resultats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resultats)
{
    ui->setupUi(this);
}

Resultats::~Resultats()
{
    delete ui;
}
