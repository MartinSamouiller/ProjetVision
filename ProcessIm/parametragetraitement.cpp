#include "parametragetraitement.h"
#include "ui_parametragetraitement.h"



#include <QtDebug>

ParametrageTraitement::ParametrageTraitement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametrageTraitement)
{
    ui->setupUi(this);

    compt = new ComptageObjet();
    couleur = new ChoixCouleur();
    detectioncou = new DetectionCouleurs();
    retrouveobj = new RetrouverObjet();
    formedete = new DetectionForme();
}

ParametrageTraitement::~ParametrageTraitement()
{
    delete ui;
}


void ParametrageTraitement::SetTypeTraitement(E_TYPE_TRAITEMENT type){
    _eTypeTraitement = type;

      //clearLayout(ui->layout_traitement, true);

      switch (type)
      {
         case COMPTAGE_OBJET:
            removeAllWidgets();

            if(compt == NULL)
              compt = new ComptageObjet();

            ui->layout_traitement->addWidget(compt);
            compt->show();
            qDebug() << "COMPTAGE_OBJET";
            break;
         case CHOIX_COULEUR:
            removeAllWidgets();
            if(couleur == NULL)
               couleur = new ChoixCouleur();

            ui->layout_traitement->addWidget(couleur);
            couleur->show();
            qDebug() << "CHOIX_COULEUR";
            break;
          case DETECTION_COULEUR:
           removeAllWidgets();
             if(detectioncou == NULL)
                detectioncou = new DetectionCouleurs();

             ui->layout_traitement->addWidget(detectioncou);
             detectioncou->show();
             qDebug() << "DETECTION_COULEUR";
             break;
          case RETROUVER_OBJET:
           removeAllWidgets();
             if(retrouveobj == NULL)
                retrouveobj = new RetrouverObjet();

             ui->layout_traitement->addWidget(retrouveobj);
             retrouveobj->show();
             qDebug() << "RETROUVER_OBJET";
             break;
          case DETECTION_FORME:
           removeAllWidgets();
             if(formedete == NULL)
                formedete = new DetectionForme();

             ui->layout_traitement->addWidget(formedete);
             formedete->show();
             qDebug() << "DETECTION_FORME";
             break;
          default:
             break;
      }


}




//Demarrage du traitement
void ParametrageTraitement::on_btn_LancerProcess_clicked()
{

}

void ParametrageTraitement::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);

        delete item;
    }
}


void ParametrageTraitement::removeAllWidgets(){

    ui->layout_traitement->removeWidget(compt);
    ui->layout_traitement->removeWidget(couleur);
    ui->layout_traitement->removeWidget(detectioncou);
    ui->layout_traitement->removeWidget(retrouveobj);
    ui->layout_traitement->removeWidget(formedete);
    compt->hide();
    couleur->hide();
    detectioncou->hide();
    retrouveobj->hide();
    formedete->hide();
}
