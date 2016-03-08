#include "comptageobjet.h"
#include "ui_comptageobjet.h"

ComptageObjet::ComptageObjet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComptageObjet)
{
    ui->setupUi(this);
    _hsv = ui->checkBox_HSV->isChecked();
    _threshold = ui->spinBox_Threshold->value();
    _sizeMorpho = ui->spinBox_OpenSize->value();
}

ComptageObjet::~ComptageObjet()
{
    delete ui;

}

void ComptageObjet::on_checkBox_HSV_clicked()
{
    _hsv = ui->checkBox_HSV->isChecked();
}

void ComptageObjet::on_spinBox_Threshold_valueChanged(int arg1)
{
    _threshold = arg1;
}

void ComptageObjet::on_spinBox_OpenSize_valueChanged(int arg1)
{
    _sizeMorpho = arg1;
}
