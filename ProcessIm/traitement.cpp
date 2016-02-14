#include "traitement.h"

#include <QDebug>
#include <QFuture>
#include <QtConcurrent>


using namespace cv;

traitement::traitement()
{

}

traitement::~traitement()
{

}

//Classification par forme
cv::Mat traitement::traitementForme(cv::Mat _matIn){


    //cv::Mat matIndex = seuillageColor(_matIn);
    //int nb = comptageObject(matIndex);

    /*QMessageBox msgBox;
    msgBox.setText(" Nombre d'objet : " + nb);
    msgBox.exec();*/

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
cv::Mat traitement::traitementCouleurDetection(cv::Mat _matIn)
{
    cv::Mat matThres;
    cv::Mat matIndex = seuillageColor(_matIn, matThres);

    cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/matThres.tif", matThres);

    int nb = comptageObject(matIndex);
    cv::Mat matColor(matIndex.rows, matIndex.cols, CV_8UC4);

    //Vector pour chaque index on a la somme de tout les niveau de gris du bouchon et le nombre de pixel du bouchon
    QVector< QPair<cv::Vec4d, int> > listColorIndexMean(nb+1);

    for(int y=0;y<_matIn.size().height;y++){
        for(int x=0;x<_matIn.size().width;x++){
            int index = matIndex.at<int>(y, x);
            if(index > 0){
                cv::Vec4b intensity = _matIn.at<cv::Vec4b>(y, x);

                matColor.at<cv::Vec4b>(y, x) = intensity;

                cv::Vec4d vectDouble = listColorIndexMean[index].first;
                vectDouble[0] = vectDouble[0] + intensity[0];
                vectDouble[1] = vectDouble[1] + intensity[1];
                vectDouble[2] = vectDouble[2] + intensity[2];
                listColorIndexMean[index].first = vectDouble;
                listColorIndexMean[index].second = listColorIndexMean[index].second + 1;
            }
        }
    }

    //On calcul les moyennes des composantes pour chaque index
    for(int i = 1; i < listColorIndexMean.size(); i++){

        cv::Vec4d vectRGBMean = listColorIndexMean[i].first;

        vectRGBMean[0] = vectRGBMean[0] / listColorIndexMean[i].second;
        vectRGBMean[1] = vectRGBMean[1] / listColorIndexMean[i].second;
        vectRGBMean[2] = vectRGBMean[2] / listColorIndexMean[i].second;
        listColorIndexMean[i].first = vectRGBMean;

        qDebug() << "Index : " << i << " R : " << QString::number(vectRGBMean[0])
                                    << " G : " << QString::number(vectRGBMean[1])
                                    << " B : " << QString::number(vectRGBMean[2]);

    }

    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;

    cv::findContours(matThres, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    // Find the rotated rectangles and ellipses for each contour
    std::vector<RotatedRect> minRect( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
    {
        minRect[i] = minAreaRect( Mat(contours[i]) );
    }

    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( 0, 0, 255 );
        // contour
        //cv::drawContours( _matIn, contours, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
        // rotated rectangle
        Point2f rect_points[4]; minRect[i].points( rect_points );
        for( int j = 0; j < 4; j++ )
            cv::line( _matIn, rect_points[j], rect_points[(j+1)%4], color, 4, 8 );
    }
    qDebug() << "Traitement fini" ;
   // cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/1matIn.tif", _matIn);
   // cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/1matIndex.tif", matIndex);

    return matIndex;
}

//Recherche d'objet
cv::Mat traitement::traitementFindObjet(cv::Mat _matIn)
{
    return _matIn;
}

//recupére une image labelisée
//compte le nombre d'objet
int traitement::comptageObject(cv::Mat _matIn )
{
    // get the image data 
    int height    = _matIn.size().height;
    int width     = _matIn.size().width;
    int max = 0;

    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
           if(_matIn.at<int>(y,x) > max){
                max = _matIn.at<int>(y,x) ;
           }
        }
    }

    return (int)max;

}

cv::Mat traitement::Overlay(cv::Mat _matIn)
{
    return _matIn;
}









cv::Mat traitement::seuillageColor(cv::Mat _matIn, cv::Mat& _matThresh)
{
    cv::Mat matHSV ;
    cv::cvtColor(_matIn , matHSV, CV_RGB2HSV);
    //cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/imgHSV.tif", matHSV);

    //On recupere les plans H S V
    cv::Mat channel[3]; ;
    cv::split(matHSV, channel);
    //Le plan 1 correspond au channel 1
    //cv::Mat planH = channel[0];
    cv::Mat planS = channel[1];
    //cv::Mat planV = channel[2];

    cv::Mat img_bw;
    cv::threshold(planS, img_bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);


    //cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/planS.tif", planS);
    //cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/img_bw.tif", img_bw);
    cv::Mat element = cv::getStructuringElement( cv::MORPH_ELLIPSE , cv::Size( 2*7 + 1, 2*7+1 ), cv::Point( 3, 3 ) );

    /// Apply the specified morphology operation
    cv::Mat matMorph;
    cv::morphologyEx( img_bw, matMorph, cv::MORPH_CLOSE, element );


    // Floodfill from point (0, 0)
    Mat im_floodfill = matMorph.clone();
    cv::floodFill(im_floodfill, cv::Point(0,0), Scalar(255));

    // Invert floodfilled image
    Mat im_floodfill_inv;
    cv::bitwise_not(im_floodfill, im_floodfill_inv);

    // Combine the two images to get the foreground.
    matMorph = (matMorph | im_floodfill_inv);

    cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/morphologyEx.tif", matMorph);

    cv::Mat labeling;
    cv::connectedComponents(matMorph, labeling);

    cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/labeling.tif", labeling);
     cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/matMorph.tif", matMorph);

    _matThresh = matMorph;

    return labeling;
}

