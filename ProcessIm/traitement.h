#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>
#include <QImage>


class traitement
{
public:
    traitement();
    ~traitement();
    //Classification par forme
    cv::Mat traitementForme(cv::Mat _matIn);
    //Comptage d'objets dans l'image
    cv::Mat traitementComptage(cv::Mat _matIn);
    //Classification par couleur
    cv::Mat traitementCouleurChoix(cv::Mat _matIn);
    //Recherche des objets ayant une couleur paramétrée
    cv::Mat traitementCouleurDetection(cv::Mat _matIn);
    //Recherche d'objet
    cv::Mat traitementFindObjet(cv::Mat _matIn);

 private:
    void comptageObject(cv::Mat _matIn );
};

#endif // TRAITEMENT_H
