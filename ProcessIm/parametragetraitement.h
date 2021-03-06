#ifndef PARAMETRAGETRAITEMENT_H
#define PARAMETRAGETRAITEMENT_H

#include <QWidget>
#include "defineprocessim.h"

#include "comptageobjet.h"
#include "choixcouleur.h"
#include "retrouverobjet.h"
#include "detectioncouleurs.h"
#include "detectionforme.h"

namespace Ui {
class ParametrageTraitement;
}

class ParametrageTraitement : public QWidget
{
    Q_OBJECT

public:
    explicit ParametrageTraitement(QWidget *parent = 0);
    ~ParametrageTraitement();

    //Definit le mode de traitement en cours
    void SetTypeTraitement(E_TYPE_TRAITEMENT type);
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void removeAllWidgets();
    E_TYPE_TRAITEMENT getTypeTraitement() {return _eTypeTraitement; };
    QString getTypeTraitementString();

    ComptageObjet *getComptageObjet(){return  compt; };
    ChoixCouleur * getChoixCouleur() {return couleur ; };
    DetectionCouleurs *getDetectionCouleur() {return detectioncou ;};
    RetrouverObjet *getRetrouverObjet(){ return retrouveobj; } ;
    DetectionForme *getDetectionForme() {return formedete;} ;

private slots:
    void on_btn_LancerProcess_clicked();

signals:
    void demarerTraitements();

private:
    Ui::ParametrageTraitement *ui;
    E_TYPE_TRAITEMENT _eTypeTraitement;
    ComptageObjet *compt ;
    ChoixCouleur *couleur ;
    DetectionCouleurs *detectioncou ;
    RetrouverObjet *retrouveobj ;
    DetectionForme *formedete ;

};

#endif // PARAMETRAGETRAITEMENT_H
