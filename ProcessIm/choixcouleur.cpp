#include "choixcouleur.h"
#include "ui_choixcouleur.h"

ChoixCouleur::ChoixCouleur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChoixCouleur)
{
    ui->setupUi(this);
}

ChoixCouleur::~ChoixCouleur()
{
    delete ui;
}
