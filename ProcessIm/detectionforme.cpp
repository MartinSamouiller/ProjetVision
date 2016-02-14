#include "detectionforme.h"
#include "ui_detectionforme.h"

DetectionForme::DetectionForme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetectionForme)
{
    ui->setupUi(this);
}

DetectionForme::~DetectionForme()
{
    delete ui;
}
