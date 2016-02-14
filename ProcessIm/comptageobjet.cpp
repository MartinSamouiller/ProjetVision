#include "comptageobjet.h"
#include "ui_comptageobjet.h"

ComptageObjet::ComptageObjet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComptageObjet)
{
    ui->setupUi(this);
}

ComptageObjet::~ComptageObjet()
{
    delete ui;
}

void ComptageObjet::on_checkBox_HSV_clicked()
{

}

void ComptageObjet::on_spinBox_Threshold_valueChanged(int arg1)
{

}

void ComptageObjet::on_spinBox_OpenSize_valueChanged(int arg1)
{

}
