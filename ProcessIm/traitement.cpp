#include "traitement.h"

#include <QDebug>
#include <QFuture>
#include <QtConcurrent>


using namespace cv;

traitement::traitement(QWidget *parent)
{

}

traitement::~traitement()
{

}

//Classification par forme
void traitement::traitementForme(cv::Mat& _matIn){


    //cv::Mat matIndex = seuillageColor(_matIn);
    //int nb = comptageObject(matIndex);

    /*QMessageBox msgBox;
    msgBox.setText(" Nombre d'objet : " + nb);
    msgBox.exec();*/

    emit traitementFinished();


}

//Comptage d'objets dans l'image
void traitement::traitementComptage(cv::Mat& _matIn, bool b_hsv, int threshold, int sizemorpho){

    cv::Mat matThres;

    //seuillage de l'image de base
    _mat_label = seuillageColor(_matIn, matThres , b_hsv,threshold, sizemorpho );

    //Comptage d'objets
    nbre_objets = comptageObject(_mat_label);

    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    cv::findContours(matThres, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    /// Get the moments
     std::vector<Moments> mu(contours.size() );
     for( int i = 0; i < contours.size(); i++ )
     {
         mu[i] = moments( contours[i], false );
     }

     ///  Get the mass centers:
     std::vector<Point2f> mc( contours.size() );
     for( int i = 0; i < contours.size(); i++ )
     {
         mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
     }

    //infos_comptage.resize(nbre_objets);
    for(int i = 0; i < nbre_objets; i++){
        S_INFOS_OBJETS objet;
        Point2f center;
        float radius;
        cv::minEnclosingCircle(contours[i], center ,radius );

        Point2f ptn = mc[i];
        objet.label = i ;
        objet.center = QPointF(ptn.x, ptn.y);
        objet.area = mu[i].m00;
        objet.radius = radius;
        //infos_comptage[i] = objet;
        infos_comptage.push_back(objet);

        std::string text = "";
        text.append("N : ");
        text.append(std::to_string(i));

        qDebug()<< QString::fromStdString(text);
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;
        int thickness = 2;

        // center the text
        cv::Point textOrg(ptn.x, ptn.y);
        // then put the text itself
        cv::putText(_mat_current, text, textOrg, fontFace, fontScale,
                Scalar::all(255),  thickness, 8);


    }


    qDebug() << "traitement fini";
    emit traitementFinished();
}

//Classification par couleur
void traitement::traitementCouleurChoix(cv::Mat& _matIn){

    emit traitementFinished();

}

//Recherche des objets ayant une couleur paramétrée
void traitement::traitementCouleurDetection(cv::Mat& _matIn)
{
    cv::Mat matThres;
    cv::Mat matIndex = seuillageColor(_matIn, matThres, true);

    //cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/matThres.tif", matThres);

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

    emit traitementFinished();

}

//Recherche d'objet
void traitement::traitementFindObjet(cv::Mat& _matIn)
{
    emit traitementFinished();
}

//recupére une image labelisée
//compte le nombre d'objet
int traitement::comptageObject(cv::Mat _matIn)
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


cv::Mat traitement::seuillageColor(cv::Mat _matIn, cv::Mat& _matThresh,  bool b_hsv, int threshold, int sizemorpho)
{
    qDebug() << " threshold " << QString::number(threshold) << " Size morpho : " << QString::number(sizemorpho);
    cv::Mat matHSV ;
    cv::cvtColor(_matIn , matHSV, CV_RGB2HSV);

    //On recupere les plans H S V
    cv::Mat channel[3]; ;
    cv::split(matHSV, channel);
    //Le plan 1 correspond au channel 1
    //cv::Mat planH = channel[0];
    cv::Mat planS = channel[1];
    //cv::Mat planV = channel[2];

    cv::Mat img_bw;

    if(threshold == -1 )
        cv::threshold(planS, img_bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    else
        cv::threshold(planS, img_bw, threshold, 255, CV_THRESH_BINARY);


    //cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/planS.tif", planS);
    //cv::imwrite("D:/Projets/ProjetVision/Baumer Image Records_V2/img_bw.tif", img_bw);
    cv::Mat element;
    if(sizemorpho != 0)
        element = cv::getStructuringElement( cv::MORPH_ELLIPSE , cv::Size( 2*sizemorpho + 1, 2*sizemorpho+1 ), cv::Point( 3, 3 ) );
    else
        element = cv::getStructuringElement( cv::MORPH_ELLIPSE , cv::Size( 2*7 + 1, 2*7+1 ), cv::Point( 3, 3 ) );

    /// Apply the specified morphology operation
    cv::Mat matMorph;
    cv::morphologyEx( img_bw, matMorph, cv::MORPH_CLOSE, element );

    //remplissage des trous :
    // Floodfill from point (0, 0)
    Mat im_floodfill = matMorph.clone();
    cv::floodFill(im_floodfill, cv::Point(0,0), Scalar(255));

    // Invert floodfilled image
    Mat im_floodfill_inv;
    cv::bitwise_not(im_floodfill, im_floodfill_inv);

    // Combine the two images to get the foreground.
    matMorph = (matMorph | im_floodfill_inv);

    cv::Mat labeling;
    int nLabels =cv::connectedComponents(matMorph, labeling);
    //Creation d'une image fausse couleur
    std::vector<Vec3b> colors(nLabels);
    colors[0] = Vec3b(0, 0, 0);//background
    for(int label = 1; label < nLabels; ++label){
       colors[label] = Vec3b( (rand()&255), (rand()&255), (rand()&255) );
    }
    Mat dst(matMorph.size(), CV_8UC3);
    for(int r = 0; r < dst.rows; ++r){
       for(int c = 0; c < dst.cols; ++c){
           int label = labeling.at<int>(r, c);
           Vec3b &pixel = dst.at<Vec3b>(r, c);
           pixel = colors[label];
        }
    }


    _matThresh = matMorph;

    //On modifie l'image courrante
    dst.copyTo(_mat_current);

    return labeling;
}

/// Resultats
///
///

