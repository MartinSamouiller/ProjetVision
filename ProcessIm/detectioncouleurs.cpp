#include "detectioncouleurs.h"
#include "ui_detectioncouleurs.h"
#include "QtDebug"

DetectionCouleurs::DetectionCouleurs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetectionCouleurs)
{
    ui->setupUi(this);
    ui->w_C1->setTitle("Couleur n°1 : ");
    ui->w_C2->setTitle("Couleur n°2 : ");
    ui->w_C3->setTitle("Couleur n°3 : ");
    ui->w_C4->setTitle("Couleur n°4 : ");
    ui->w_C5->setTitle("Couleur n°5 : ");

    on_spinBox_valueChanged(ui->spinBox->value());

}

DetectionCouleurs::~DetectionCouleurs()
{
    delete ui;
}

//Desactive les widget color en fonction du nombre de couleurs que l'on veut detecter
void DetectionCouleurs::on_spinBox_valueChanged(int arg1)
{
    /*ui->w_C1->setEnabled(false);
    ui->w_C2->setEnabled(false);
    ui->w_C3->setEnabled(false);
    ui->w_C4->setEnabled(false);
    ui->w_C5->setEnabled(false);


    switch (arg1) {
      case 1:
        ui->w_C1->setEnabled(true);
        break;
      case 2:
        ui->w_C1->setEnabled(true);
        ui->w_C2->setEnabled(true);
        break;
      case 3:
        ui->w_C1->setEnabled(true);
        ui->w_C2->setEnabled(true);
        ui->w_C3->setEnabled(true);

        break;
      case 4:
        ui->w_C1->setEnabled(true);
        ui->w_C2->setEnabled(true);
        ui->w_C3->setEnabled(true);
        ui->w_C4->setEnabled(true);
        break;
      case 5:
        ui->w_C1->setEnabled(true);
        ui->w_C2->setEnabled(true);
        ui->w_C3->setEnabled(true);
        ui->w_C4->setEnabled(true);
        ui->w_C5->setEnabled(true);
        break;
      default:
        qDebug() << "ERROR MODE IMPOSSIBLE";
        break;
      }
*/
        ui->w_C1->hide();
        ui->w_C2->hide();
        ui->w_C3->hide();
        ui->w_C4->hide();
        ui->w_C5->hide();


        switch (arg1) {
          case 1:
            ui->w_C1->show();
            break;
          case 2:
            ui->w_C1->show();
            ui->w_C2->show();
            break;
          case 3:
            ui->w_C1->show();
            ui->w_C2->show();
            ui->w_C3->show();

            break;
          case 4:
            ui->w_C1->show();
            ui->w_C2->show();
            ui->w_C3->show();
            ui->w_C4->show();
            break;
          case 5:
            ui->w_C1->show();
            ui->w_C2->show();
            ui->w_C3->show();
            ui->w_C4->show();
            ui->w_C5->show();
            break;
          default:
            qDebug() << "ERROR MODE IMPOSSIBLE";
            break;
          }

}
