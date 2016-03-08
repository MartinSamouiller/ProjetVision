#include "histogramme.h"
#include "ui_histogramme.h"

#include "imagewindows.h"
#include <QMdiSubWindow>
#include "qimagetomat.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#include <QMessageBox>

Histogramme::Histogramme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Histogramme)
{
    ui->setupUi(this);
}

Histogramme::Histogramme(QImage * im, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Histogramme)
{
    ui->setupUi(this);

    if(im ==  NULL)
        QMessageBox::warning(this, tr("Histogramme"), tr("Probléme image inexistante"),  QMessageBox::Cancel, QMessageBox::Ok);
    else{
        im_courante = im;
        createHisto();
    }


}

Histogramme::~Histogramme()
{
    delete ui;
}


void Histogramme::createHisto(){

    if(im_courante ==  NULL)
        return;

  /* if(im_courante->isGrayscale()){

         cv::Mat im_histo = QImageToMat::QImageToCvMat(*im_courante);

         cv::Mat hist;

         /// Compute the histograms:
         cv::calcHist( &im_histo, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );

         std::vector<unsigned long> h = image_ndg.histogramme(ui->checkBox->isChecked());

         m_scene = new QGraphicsScene(this);   // création scene
         m_scene->clear();

         QBrush brosseBleue(Qt::blue);   // création brosse bleue
         QPen crayon(Qt::black);   // création crayon
         crayon.setWidth(2);  // taille crayon

        // m_rectangle = m_scene->addRect(0,0,10,100,crayon,brosseBleue);

         //Permet de recaler l'histogramme en fonction de la hauteur max de la fenetre
         int val_histMax = ui->graphicsView_histo->height();

         int MaxHisto = 0;

         //recherche du pic maximum dans l'histogramme -> permet de redefinir en hauteur l'histogramme
         for(int i = 0; i<h.size(); i++){
             if(MaxHisto < h[i])
                 MaxHisto = h[i];
         }
         int res = 0;
         int pas = ui->graphicsView_histo->width()/256;
         qDebug() << ui->graphicsView_histo->width();

         //Creation de l'histogramme (on ajoute un rectangle de largeur variable -> depend de la largeur de la fenetre)
         int y = 0;
         for (int i=0;i<256;i++){
             res = h[i]*val_histMax/MaxHisto;
             m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(pas, -res)));
             y = y +pas;
         }

         ui->graphicsView_histo->setScene(m_scene);
     }else{*/
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;

    cv::Mat im_histo = QImageToMat::QImageToCvMat(*im_courante);
    /// Separate the image in 3 places ( B, G and R )
    std::vector<cv::Mat> bgr_planes;
    cv::split( im_histo, bgr_planes );

    cv::Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    cv::calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );


    /// Normalize the result to [ 0, histImage.rows ]
    //cv::normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
   // cv::normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
   // cv::normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    std::vector<std::vector<unsigned long>> h;
    h.resize(3);
    h[0].resize(histSize );
    h[1].resize(histSize );
    h[2].resize(histSize );

    if(b_hist.size() == g_hist.size() && r_hist.size() == g_hist.size()){
        for(int i = 0; i< histSize ; i++)
        {
            h[0][i] = static_cast<unsigned long>(r_hist.at<float>(i));
            h[1][i] = static_cast<unsigned long>(g_hist.at<float>(i));
            h[2][i] = static_cast<unsigned long>(b_hist.at<float>(i));
            qDebug() << "Index :" << QString::number(i);
            qDebug() << "R :" << QString::number(h[0][i]);
            qDebug() << "G :" << QString::number( h[1][i]);
            qDebug() << "B :" << QString::number(h[2][i]);
        }
    }



     m_scene = new QGraphicsScene(this);   // création scene
     m_scene->clear();

     QBrush brosseBleue(Qt::blue);   // création brosse bleue

    // m_rectangle = m_scene->addRect(0,0,10,100,crayon,brosseBleue);
     ui->graphicsView_histo->resize(ui->graphicsView_histo->width(), 100);
     float val_histMax = ui->graphicsView_histo->height();

     float MaxHisto = 0.f;
     for(int y = 0; y<3; y++){
         for(int i = 0; i<histSize; i++){
             if(MaxHisto < h[y][i])
                 MaxHisto = h[y][i];
         }
     }

     int res1 = 0;
     int res2 = 0;
     int res3 = 0;
     //float pas = (float)ui->graphicsView_histo->width()/256.f;

     int y = 0;

     float coef = val_histMax/MaxHisto;
     qDebug() << "Coef : " << QString::number(coef);
     qDebug() << "MaxHisto : " << QString::number(MaxHisto);
     qDebug() << "MaxHisto : " << QString::number(val_histMax);
     //On créer les histogrammes sur les 3 plans
     QPen crayon(Qt::red);   // création crayon
     QPen crayon2(Qt::green);   // création crayon
     QPen crayon3(Qt::blue);   // création crayon

     for (int i=0;i<histSize ;i++){
         res1 = (int)((float)h[0][i]*coef);
         m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(3, -res1)),crayon );
         qDebug() << "R :" << QString::number(res1);
         res2 = (int)((float)h[1][i]*coef);
         m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(3, -res2)), crayon2);
         qDebug() << "G :" << QString::number(res2);
         res3 = (int)((float)h[2][i]*coef);
         m_rectangle = m_scene->addRect(QRectF(QPoint(y, 0), QSize(3, -res3)), crayon3);
         qDebug() << "B :" << QString::number(res3);
         //y = y +pas;
         y=y+4;
     }


     ui->graphicsView_histo->setScene(m_scene);



}

