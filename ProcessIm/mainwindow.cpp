#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QSplitter>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDesktopWidget>
#include <QMessageBox>


#include "histogramme.h"
#include "imagewindows.h"
#include "infowindows.h"
#include "qimagetomat.h"
#include "traitement.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setLayout(ui->Layout_Travail);

    /*InfoWindows *info = new InfoWindows();
    info -> setWindowModality (Qt::ApplicationModal);
    info->show();*/

    showNormal();

    imageLbl=new qlabel_image();

    //Signal émit par la class qlabel_image pour la lecture en dynamique de la position des pixels
    connect(imageLbl, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(imageLbl, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
    connect(imageLbl, SIGNAL(Mouse_ClickLeft()), this, SLOT(MouseClickLeft()));
    connect(imageLbl, SIGNAL(Mouse_ReleasePos()), this, SLOT(Mouse_release_pos()));
    imageLbl->setMouseTracking(true);



}

MainWindow::~MainWindow()
{
    //message
    delete ui;
}
/*
void MainWindow::on_actionOuvrir_une_image_triggered()
{
    m_index_image += 1;
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.bmp)");
    QFileInfo file(fichier);


    QImage *im_tmp = new QImage(fichier);

    QString name_image = file.fileName();


    ImageWindows *ImWin = new ImageWindows(*im_tmp,name_image );
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(ImWin);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    ui->mdiArea_Simulation->addSubWindow(subWindow1);
    subWindow1->show();

}*/




void MainWindow::on_actionQuitter_triggered()
{
      close();
}

void MainWindow::on_actionTutoriel_triggered()
{
    QMessageBox::information(this, "Aide", "Affiche le <strong>tutoriel<strong>");
}

void MainWindow::on_actionA_propos_de_ProcessIm_triggered()
{
    InfoWindows *info = new InfoWindows();
    info -> setWindowModality (Qt::WindowModal);
    info->show();
    //QMessageBox::information(this, "A propos", "Créateur : ...");
}


//Si erreur de externe non résolu : vérifier les dossiers build

void MainWindow::on_actionDossier_de_travail_triggered()
{

}
/*
void MainWindow::on_cbTraitement_currentIndexChanged(const QString &arg1)
{
    //CImageNdg *image_traitement = new CImageNdg(*image_courante);

    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1 =  ui->mdiArea_Simulation->currentSubWindow();
    if(subWindow1 != 0){
        ImageWindows *imCurrent = (ImageWindows*)subWindow1->widget();
            QImage imTransform = imCurrent->getImageCurrent();
            ui->lbl_curren_image_selectionner->setText(imCurrent->getImageName());

            /*if (arg1 == "Histogramme")
            {
                Histogramme *histo = new Histogramme(imTransform);
                ui->sa_outil->setWidget(histo);
            }*/

    /*}else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Aucune image n'est ouverte");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }


}*/

/*
void MainWindow::on_cbAnalyse_currentIndexChanged(const QString &arg2)
{
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1 =  ui->mdiArea_Simulation->currentSubWindow();
    if(subWindow1 != 0){
        ImageWindows *imCurrent = (ImageWindows*)subWindow1->widget();
        QImage imTransform = imCurrent->getImageCurrent();
        ui->lbl_curren_image_selectionner->setText(imCurrent->getImageName());

    }else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Aucune image n'est ouverte");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }
}

*/

//recupére l'image de
QImage * MainWindow::getImageSimulation(){

    if(ui->scrollArea->widget() != NULL)
        return NULL;

    qlabel_image *imageLbl = (qlabel_image*)ui->scrollArea->widget();
    const QPixmap *pixelMap = imageLbl->pixmap();
    QImage img = pixelMap->toImage();

    return &img;
}

void MainWindow::Mouse_current_pos()
{

     qlabel_image *imageLbl = (qlabel_image*)ui->scrollArea->widget();
     const QPixmap *pixelMap = imageLbl->pixmap();
     QImage img = pixelMap->toImage();

    ui->label_XY->setText(QString("X = %1, Y= %2").arg(imageLbl->x/*/m_coeffZoom*/).arg(imageLbl->y/*/m_coeffZoom*/));
    if(pixelMap != NULL){

        QRgb rgb = img.pixel(imageLbl->x/*/m_coeffZoom*/, imageLbl->y/*/m_coeffZoom*/);
        ui->label_RGB->setText(QString("R = %1 , G = %2 ,  B = %3")
                                        .arg(qRed(rgb))
                                        .arg(qGreen(rgb))
                                        .arg(qBlue(rgb)));

    }
}

void MainWindow::Mouse_pressed()
{

}

void MainWindow::MouseClickLeft()
{

}

void MainWindow::Mouse_release_pos()
{
   // ui->lbl_y->setText(QString("X = %1, Y= %2").arg(imageLbl->xr).arg(imageLbl->yr));
}



void MainWindow::on_actionOuvrir_triggered()
{
    //Add Image
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString());
    imcurrent = new QImage(fichier);
    mat_current = QImageToMat::QImageToCvMat(*imcurrent, false);


    imageLbl->setScaledContents(true);

    imageLbl->setFixedWidth(imcurrent->width());
    imageLbl->setFixedHeight(imcurrent->height());

    imageLbl->setPixmap(QPixmap::fromImage(*imcurrent));
    ui->scrollArea->setWidget(imageLbl);


}

void MainWindow::on_checkBox_Histogramme_clicked()
{

    if(ui->scrollArea_Histogramme->widget() != NULL)
        delete ui->scrollArea_Histogramme->widget();

    //On active l'histogramme si on veut qu'il s'affiche
    if(ui->checkBox_Histogramme->isChecked()){
        QImage *img = getImageSimulation();
        Histogramme *histo = new Histogramme(img);
        ui->scrollArea_Histogramme->setWidget(histo);
        ui->scrollArea_Histogramme->setHidden(false);

    }else
        ui->scrollArea_Histogramme->setHidden(true);

}




void MainWindow::on_pushButton_clicked()
{
    traitement tr;

    if(ui->radioButton_Forme->isChecked()){
        tr.traitementForme(mat_current);
    }
    else if (ui->radioButton_Comptage->isChecked())
    {
        tr.traitementComptage(mat_current);
    }
    else if (ui->radioButton_CouleurChoix->isChecked())
    {
        tr.traitementCouleurChoix(mat_current);
    }
    else if(ui->radioButton_CouleurDetection->isChecked())
    {
        tr.traitementCouleurDetection(mat_current);
    }
    else if(ui->radioButton_Findobjet->isChecked())
    {
        tr.traitementFindObjet(mat_current);
    }
    else
    {
        //QMessageBox::warning(this, tr("Traitement"), tr("Selectionner un mode ! "),  QMessageBox::Cancel, QMessageBox::Ok);
    }

}


