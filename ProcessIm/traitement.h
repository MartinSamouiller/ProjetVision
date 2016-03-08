#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>
#include <QImage>

#include "defineprocessim.h"

class traitement : public QWidget
{
    Q_OBJECT

public:
    explicit traitement(QWidget *parent = 0);
    //traitement();
    ~traitement();
    //Classification par forme
    void traitementForme(cv::Mat& _matIn);
    //Comptage d'objets dans l'image
    void traitementComptage(cv::Mat& _matIn, bool b_hsv, int threshold, int sizemorpho);
    //Classification par couleur
    void traitementCouleurChoix(cv::Mat& _matIn);
    //Recherche des objets ayant une couleur paramétrée
    void traitementCouleurDetection(cv::Mat &_matIn);
    //Recherche d'objet
    void traitementFindObjet(cv::Mat& _matIn);

    //Recupération du nombre d'objets
    void getResultatComptage(int& nbrObjet){nbrObjet = nbre_objets;}
    std::vector<S_INFOS_OBJETS> getResultatComptage(){return infos_comptage; }

    inline cv::Mat getMatCurrent(){return _mat_current;}
    inline cv::Mat getMatLabel(){return _mat_label;}

 private:
    int comptageObject(cv::Mat _matIn);
    cv::Mat seuillageColor(cv::Mat _matIn, cv::Mat &_matThresh, bool b_hsv, int threshold = -1, int sizemorpho = 7);
    int nbObjet(cv::Mat _matIn);
    //cv::Mat traitementCouleurDetectionThread(cv::Mat _matIn);

signals:
    void traitementFinished();
    void traitementComptageFinished(int nbr_objet); //renvoi le nombre d'objets detectés

private:
    int nbre_objets = 0; //Permet de notifier le résultat du comptage d'objet.
    std::vector<S_INFOS_OBJETS> infos_comptage;

    cv::Mat _mat_current;
    cv::Mat _mat_label;

};

#endif // TRAITEMENT_H
