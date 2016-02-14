#include "retrouverobjet.h"
#include "ui_retrouverobjet.h"

RetrouverObjet::RetrouverObjet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RetrouverObjet)
{
    ui->setupUi(this);
}

RetrouverObjet::~RetrouverObjet()
{
    delete ui;
}
