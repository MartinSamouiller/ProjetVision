#include "traitement.h"

#include <QDebug>

traitement::traitement()
{

}

traitement::~traitement()
{

}

//Classification par forme
cv::Mat traitement::traitementForme(cv::Mat _matIn){
    comptageObject(_matIn );
    return _matIn;

}

//Comptage d'objets dans l'image
cv::Mat traitement::traitementComptage(cv::Mat _matIn){

return _matIn;

}

//Classification par couleur
cv::Mat traitement::traitementCouleurChoix(cv::Mat _matIn){

return _matIn;
}

//Recherche des objets ayant une couleur paramétrée
cv::Mat traitement::traitementCouleurDetection(cv::Mat _matIn){
return _matIn;

}

//Recherche d'objet
cv::Mat traitement::traitementFindObjet(cv::Mat _matIn){

    return _matIn;

}

void traitement::comptageObject(cv::Mat _matIn ){

    cv::Mat matHSV ;
    cv::cvtColor(_matIn , matHSV, CV_RGB2HSV);
    cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/imgHSV.tif", matHSV);

    //On recupere les plans H S V
    cv::Mat channel[3]; ;
    cv::split(matHSV, channel);
    //Le plan 1 correspond au channel 1
    cv::Mat planH = channel[1];
    cv::Mat img_bw;
    cv::threshold(planH, img_bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/img_bw.tif", img_bw);


    /*cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/channel1.tif", channel[0]);
    cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/channel2.tif", channel[1]);
    cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/channel3.tif", channel[2]);
    qDebug() << "comptage objet";*/

}
