#include "detectioncouleurs.h"
#include "ui_detectioncouleurs.h"

DetectionCouleurs::DetectionCouleurs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetectionCouleurs)
{
    ui->setupUi(this);
}

DetectionCouleurs::~DetectionCouleurs()
{
    delete ui;
}
