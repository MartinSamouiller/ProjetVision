#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QSplitter>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDesktopWidget>
#include <QMessageBox>

#include <QGraphicsPixmapItem>


#include "histogramme.h"
#include "imagewindows.h"
#include "infowindows.h"
#include "qimagetomat.h"
#include "defineprocessim.h"
#include "couleurschoix.h"

#include "bgapi2_genicam.hpp"


using namespace BGAPI2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showNormal();

    imageLbl = new qlabel_image();

    //Signal émit par la class qlabel_image pour la lecture en dynamique de la position des pixels
    connect(imageLbl, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(imageLbl, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
    connect(imageLbl, SIGNAL(Mouse_ClickLeft()), this, SLOT(MouseClickLeft()));
    connect(imageLbl, SIGNAL(Mouse_ReleasePos()), this, SLOT(Mouse_release_pos()));

    connect(this, SIGNAL(FinishInit()), this, SLOT(slotInitCameraFiniched()));
    connect(this, SIGNAL(ErrorInitCamera()), this, SLOT(slotInitCameraError()));

    QObject::connect(ui->radioButton_Comptage,SIGNAL(clicked(bool)),this,SLOT(slotRadioButtonMode(bool)));
    QObject::connect(ui->radioButton_CouleurChoix,SIGNAL(clicked(bool)),this,SLOT(slotRadioButtonMode(bool)));
    QObject::connect(ui->radioButton_CouleurDetection,SIGNAL(clicked(bool)),this,SLOT(slotRadioButtonMode(bool)));
    QObject::connect(ui->radioButton_Findobjet,SIGNAL(clicked(bool)),this,SLOT(slotRadioButtonMode(bool)));
    QObject::connect(ui->radioButton_Forme,SIGNAL(clicked(bool)),this,SLOT(slotRadioButtonMode(bool)));

    imageLbl->setMouseTracking(true);

    ui->pushButton_LEDConnection->setStyleSheet("background-color: red");
    ui->pushButton_LED_EtatTraite->setStyleSheet("background-color: red");

    //Creation de la fenetre de traitement
    param = new ParametrageTraitement();
    //Fenetre de résultats des traitements
    res = new Resultats();
    QObject::connect(param,SIGNAL(demarerTraitements()),this,SLOT(slotDemarerTraitement()));

    //permet de detecter quand le traitement et fini
    QObject::connect(&_Traitement,SIGNAL(traitementFinished()),this,SLOT(slotTraitementFinish()));

    //Met a jour le mode par défaut
    ui->radioButton_CouleurDetection->setChecked(true);
    slotRadioButtonMode(true);

    //On cache les deux options
    ui->radioButton_Forme->hide();
    ui->radioButton_Findobjet->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

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


//recupére l'image de
/*QImage * MainWindow::getImageSimulation(){

    if(ui->scrollArea->widget() != NULL)
        return NULL;

    qlabel_image *imageLbl = (qlabel_image*)ui->scrollArea->widget();
    const QPixmap *pixelMap = imageLbl->pixmap();
    QImage img = pixelMap->toImage();

    return &img;
}*/

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

    int nbr_objet_max;
    _Traitement.getResultatComptage(nbr_objet_max);
    if(_bdisplayRescomptage){
        if(res ){
            int value = mat_label.at<int>(imageLbl->y,imageLbl->x) ;
            if(value != 0){
                res->setSelectRowTab(nbr_objet_max - value);//changement de la ligne du tableau résultat en fonction du label
                ui->label_Label->setText(QString("Label objet %1").arg(value));
            }

        }
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

    ui->tab_Menu->setCurrentWidget(ui->tab_Simulation);


}

void MainWindow::on_checkBox_Histogramme_clicked()
{

    if(ui->scrollArea_Histogramme->widget() != NULL)
        delete ui->scrollArea_Histogramme->widget();

    //On active l'histogramme si on veut qu'il s'affiche
    if(ui->checkBox_Histogramme->isChecked()){
        //QImage *img = getImageSimulation();
        Histogramme *histo = new Histogramme(imcurrent);
        ui->scrollArea_Histogramme->setWidget(histo);
        ui->scrollArea_Histogramme->resize(histo->size());
        ui->scrollArea_Histogramme->setHidden(false);
        qDebug() << "Display histogramme";

    }else
        ui->scrollArea_Histogramme->setHidden(true);

}



/*
void MainWindow::on_pushButton_clicked()
{


}
*/

/*
void MainWindow::on_pushButton_LiveStop_clicked()
{
   pDevice->GetRemoteNode("AcquisitionStop")->Execute();

   pDataStream->StopAcquisition();
   bufferList->DiscardAllBuffers();
   while( bufferList->size() > 0)
   {
       pBuffer = bufferList->begin()->second;
       bufferList->RevokeBuffer(pBuffer);
       delete pBuffer;
   }

   pDataStream->Close();
   pDevice->Close();
   pInterface->Close();
   pSystem->Close();
   BGAPI2::SystemList::ReleaseInstance();

   std::cout << "Input any number to close the program:";
}*/

void MainWindow::on_pushButton_Snap_clicked()
{
    QFuture<int> t1 = QtConcurrent::run(this, &MainWindow::Snap);
}


void MainWindow::slotInitCameraFiniched(){
    createMsgError(_msgInit);
}

void MainWindow::slotInitCameraError(){
    createMsgError(_msgError);
}

void MainWindow::slotSnapFinished(){
    createMsgError(_msgSnap);
}


int MainWindow::InitCameraBauhmer(){

    _msgInit = "";
    qDebug() << "Connection Init Camera bauhmer";
    try
    {
        systemList = SystemList::GetInstance();
        systemList->Refresh();
        _msgInit.append("5.1.2 Detected systems: ");
        _msgInit.append(QString::number(systemList->size()));
        _msgInit.append("\n");

    }
    catch (BGAPI2::Exceptions::IException& ex)
    {
        _msgError.append("ExceptionType: ");  _msgError.append(QString(ex.GetType().get()));
        _msgError.append("ErrorDescription: ");  _msgError.append(QString(ex.GetErrorDescription().get()));
        _msgError.append("in function: ");  _msgError.append(QString(ex.GetFunctionName().get()));
        emit ErrorInitCamera();
    }

    for (SystemList::iterator sys = systemList->begin(); sys != systemList->end(); sys++)
    {
        sys->second->Open();
        sSystemID = sys->first;
        break;
    }

    if (sSystemID == ""){
        _msgError.append(_msgInit);
        _msgError.append("NO SYSTEM FOUND");
        emit ErrorInitCamera();
        return 0; // no system found
    }
    else
        pSystem = (*systemList)[sSystemID];

    interfaceList = pSystem->GetInterfaces();
    interfaceList->Refresh(100);
     _msgInit.append("5.1.4 Detected interfaces: ");
     _msgInit.append(QString::number(interfaceList->size()));
     _msgInit.append("\n");

    for(InterfaceList::iterator ifc = interfaceList->begin(); ifc != interfaceList->end(); ifc++)
    {
        ifc->second->Open();
        sInterfaceID = ifc->first;
        break;
    }

    if (sInterfaceID == ""){
        _msgError.append(_msgInit);
        _msgError.append("NO INTERFACE FOUND");
        emit ErrorInitCamera();
        return 0; // no system found
    }
    else
        pInterface = (*interfaceList)[sInterfaceID];

    deviceList = pInterface->GetDevices();
    deviceList->Refresh(100);
    _msgInit.append("5.1.6 Detected devices: ");
    _msgInit.append(QString::number(deviceList->size()));
    _msgInit.append("\n");

    for (DeviceList::iterator dev = deviceList->begin(); dev != deviceList->end(); dev++)
    {
        dev->second->Open();
        sDeviceID = dev->first;
        break;
    }

    if (sDeviceID == ""){
        _msgError.append(_msgInit);
        _msgError.append("NO DEVICE FOUND");
        emit ErrorInitCamera();
        return 0; //
    }
    else
        pDevice = (*deviceList)[sDeviceID];

    datastreamList = pDevice->GetDataStreams();
    datastreamList->Refresh();

    _msgInit.append("5.1.8 Detected datastreams: " );
    _msgInit.append(QString::number(datastreamList->size()));
    _msgInit.append("\n");

    for(DataStreamList::iterator dst= datastreamList->begin();dst != datastreamList->end();dst++)
    {
        dst->second->Open();
        sDataStreamID = dst->first;
        break;
    }

    if (sDataStreamID == ""){
        _msgError.append(_msgInit);
        _msgError.append("NO DATASTREAM FOUND");
        emit ErrorInitCamera();
        return 0; //
    }
    else
        pDataStream = (*datastreamList)[sDataStreamID];

    bufferList = pDataStream->GetBufferList();
    for(int i=0; i<4; i++) // 4 buffers using internal buffers
    {
        pBuffer = new BGAPI2::Buffer();
        bufferList->Add(pBuffer);
    }

    _msgInit.append("5.1.10 Announced buffers: " );
    _msgInit.append(QString::number(bufferList->size()));
    _msgInit.append("\n");

    bufferList = pDataStream->GetBufferList();

    int uPayloadSize = 100000;
    bo_uint64 payloadsize = pDataStream->GetDefinesPayloadSize() ?
    pDataStream->GetPayloadSize() : pDevice->GetPayloadSize();
    for(int i=0; i<4; i++) // 4 buffers using external allocated memory
    {
        unsigned char * pMemory = (unsigned char*)malloc(uPayloadSize);
        // use free(pMemory) when releasing resources
        pBuffer = new BGAPI2::Buffer((void*)pMemory, uPayloadSize, nullptr);
        bufferList->Add(pBuffer);
    }

    for (BufferList::iterator buf = bufferList->begin(); buf != bufferList->end(); buf++)
    {
        buf->second->QueueBuffer();
    }

    _msgInit.append("5.1.11 Queued buffers: ");
    _msgInit.append(QString::number( bufferList->GetQueuedCount()));
    _msgInit.append("\n");

    ui->pushButton_LEDConnection->setStyleSheet("background-color: green");

    emit FinishInit();

    return 1;

}

int MainWindow::Snap(){

    if(pDataStream == NULL ||pDevice == NULL ){
        createMsgError("NO DEVICE FOUND ! Connecter la camera !");
        return -1;
    }

    pDataStream->StartAcquisitionContinuous();

    pDevice->GetRemoteNode("AcquisitionStart")->Execute();


    BGAPI2::Buffer * pBufferFilled = NULL;
    try
    {
        pBufferFilled = pDataStream->GetFilledBuffer(1000);
        if(pBufferFilled == NULL)
        {
            std::cout << "Error: Buffer Timeout after 1000 msec" << std::endl;
        }
        else
        {
            std::cout << " Image " << pBufferFilled->GetFrameID() << std::endl;
            std::cout << " received in memory address " << pBufferFilled->GetMemPtr() << std::endl;
            std::cout << " Image height : " << pBufferFilled->GetHeight()  << std::endl;
            std::cout << " Image Width : " << pBufferFilled->GetWidth()  << std::endl;
            std::cout << " Image pixel format : " << pBufferFilled->GetPixelFormat()  << std::endl;
            std::cout << " Buffer size : " << pBufferFilled->GetMemSize()  << std::endl;
            //QImage img((uchar*)pBufferFilled->GetMemPtr(), pBufferFilled->GetWidth() ,pBufferFilled->GetHeight(), QImage::Format_Indexed8);

            BGAPI2::ImageProcessor *imgProcessor = BGAPI2::ImageProcessor::GetInstance() ;

            BGAPI2::Image* image = imgProcessor->CreateImage(pBufferFilled->GetWidth(), pBufferFilled->GetHeight(),pBufferFilled->GetPixelFormat(), pBufferFilled->GetMemPtr(), pBufferFilled->GetMemSize());

            BGAPI2::Image* imageTransform =  imgProcessor->CreateTransformedImage(image, "RGB8Packed");

            im_Acqui = QImage((uchar*)imageTransform->GetBuffer(), pBufferFilled->GetWidth() ,pBufferFilled->GetHeight(), QImage::Format_RGB888);
            //QPixmap imgAff;

            QPixmap imgAff;
            imgAff = QPixmap::fromImage(im_Acqui);

            //ui->lbl_live->setPixmap(imgAff);
           QGraphicsScene* scene = new QGraphicsScene();
           QGraphicsView* view = ui->graphicsView_Live;
           view->setScene(scene);
           QGraphicsPixmapItem* item = new QGraphicsPixmapItem(imgAff);
           scene->addItem(item);
           view->show();

        }
    }
    catch (BGAPI2::Exceptions::IException& ex)
    {
        std::cout << "ExceptionType: " << ex.GetType() << std::endl;
        std::cout << "ErrorDescription: " << ex.GetErrorDescription() << std::endl;
        std::cout << "in function: " << ex.GetFunctionName() << std::endl;
    }

    pBufferFilled->QueueBuffer();

    return 0;
}

void MainWindow::on_pushButton_Connection_clicked()
{
    t_connectionCamera = QtConcurrent::run(this, &MainWindow::InitCameraBauhmer); 
}


//Copier/coller
void MainWindow::on_bout_calibrage_clicked()
{
    // Etape 1 acquérir une image
    // Etape 2 Calculer la taille de l'objet (en x et y)
    // Etape 3 Caluler les coord en (en x et y) pour le robot
    _dim_x_pix = 100; // mettre taille en x en pixel
    _dim_y_pix = 100; // mettre taille en y en pixel
    _pos_x_pix = 50; // Mettre coord en x en pixel
    _pos_y_pix = 100; // Mettre coord en y en pixel

    //Récupération des valeurs de l'interface
    double taille_image_l_pix = ui->box_im_l_pix->value();
    double taille_image_h_pix = ui->box_im_h_pix->value();
    double taille_image_l_mm = ui->box_im_l_mm->value();
    double taille_image_h_mm = ui->box_im_h_mm->value();

    //Conversion
    double convx = taille_image_h_mm/taille_image_h_pix;
    double convy = taille_image_l_mm/taille_image_l_pix;

    //Valeurs en mm
    double dim_x_mm = _dim_x_pix * convx;
    double dim_y_mm = _dim_y_pix * convy;
    double pos_x_mm = _pos_x_pix * convx;
    double pos_y_mm = _pos_y_pix * convy;

    //Affichage
    ui->box_obj_x->setValue(dim_x_mm);
    ui->box_obj_y->setValue(dim_y_mm);
    ui->box_coord_x->setValue(pos_x_mm);
    ui->box_coord_y->setValue(pos_y_mm);

}

void MainWindow::on_apply_reg_clicked()
{
    if(pDevice == NULL ){
        createMsgError("NO DEVICE FOUND ! Connecter la camera !");
        return;
    }

    //Temps d'exposition
    pDevice->GetRemoteNode("ExposureTime")->SetDouble(ui->box_expo->value());

    //Pixel Format
    QString pix = ui->pixel_format->currentText();
    const char *pixformat = pix.toLatin1();
    BGAPI2::String pixf;
    pixf.set(pixformat);
    pDevice->GetRemoteNode("PixelFormat")->SetString(pixf);

    //HDR
    bool hdr = ui->HDR->currentIndex();
    pDevice->GetRemoteNode("HDREnable")->SetBool(hdr);

}


void MainWindow::createMsgError(QString message){

    qDebug() << message;
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();

}


void MainWindow::on_btn_ParametrageMode_clicked()
{
    param->show();
    qApp->setActiveWindow(param);
}


void MainWindow::slotRadioButtonMode(bool checked){

    if(ui->radioButton_Comptage->isChecked())
        param->SetTypeTraitement(COMPTAGE_OBJET);
    if(ui->radioButton_CouleurChoix->isChecked())
        param->SetTypeTraitement(CHOIX_COULEUR);
    if(ui->radioButton_CouleurDetection->isChecked())
        param->SetTypeTraitement(DETECTION_COULEUR);
    if(ui->radioButton_Findobjet->isChecked())
        param->SetTypeTraitement(RETROUVER_OBJET);
    if(ui->radioButton_Forme->isChecked())
        param->SetTypeTraitement(DETECTION_FORME);

    qDebug() << "Clicked radio button";
    qApp->setActiveWindow(param);
}



void MainWindow::on_pushButton_Save_clicked()
{
    if(!im_Acqui.isNull()){

        QString fichier = QFileDialog::getSaveFileName(this, "Sauvegarder une image", QString());
        im_Acqui.save(fichier);
        qDebug() << "Image sauvegardée";
    }

}

void MainWindow::on_pushButton_Detection_clicked()
{
    if(imcurrent != NULL)
        delete imcurrent;

    imcurrent = new QImage(im_Acqui);
    mat_current = QImageToMat::QImageToCvMat(*imcurrent, false);

    imageLbl->setScaledContents(true);
    imageLbl->setFixedWidth(imcurrent->width());
    imageLbl->setFixedHeight(imcurrent->height());

    imageLbl->setPixmap(QPixmap::fromImage(*imcurrent));
    ui->scrollArea->setWidget(imageLbl);

    ui->tab_Menu->setCurrentWidget(ui->tab_Simulation);

}



///Permet de lancer les traitements dans des thread séparés
void MainWindow::slotDemarerTraitement(){

    //En mode comptage on va afficher une selection sur les resultats en fonction de l'image de label
    //on ne veut pas que ce mode soit actif pour les autres traitements
    _bdisplayRescomptage = false;

    qDebug() << "Lancer traitement : ";
    ui->pushButton_LED_EtatTraite->setStyleSheet("background-color: red");
    E_TYPE_TRAITEMENT typeTraitement =  param->getTypeTraitement();
    qDebug() << param->getTypeTraitementString();

    switch (typeTraitement)
    {
       case COMPTAGE_OBJET:
          demarrageTraiComptage();
          break;
       case CHOIX_COULEUR:
          demarrageTraiCouleurChoix();
          break;
       case DETECTION_COULEUR:
           demarrageTraiCouleurDetection();
           break;
       case RETROUVER_OBJET:
           demarrageTraiFindObjet();
           break;
       case DETECTION_FORME:
           demarrageTraiForme();
           break;
       default:
          QMessageBox::warning(this, tr("Traitement"), tr("Selectionner un mode ! "),  QMessageBox::Cancel, QMessageBox::Ok);
          break;
    }

}
///Lancement du traitement de comptage d'objet en fonction des paramétres récupérés dans l'IHM
void MainWindow::demarrageTraiComptage(){

    bool hsv = param->getComptageObjet()->getHSV();
    int threshold = param->getComptageObjet()->getThreshold();
    int sizemorpho = param->getComptageObjet()->getSizeMorpho();

    t1 = QtConcurrent::run(&this->_Traitement, &traitement::traitementComptage, mat_current, hsv, threshold, sizemorpho);

}

void MainWindow::demarrageTraiCouleurChoix(){
    t1 = QtConcurrent::run(&this->_Traitement, &traitement::traitementCouleurChoix, mat_current);

}

void MainWindow::demarrageTraiCouleurDetection(){

    t1 = QtConcurrent::run(&this->_Traitement, &traitement::traitementCouleurDetection, mat_current);
}

void MainWindow::demarrageTraiFindObjet(){

    t1 = QtConcurrent::run(&this->_Traitement, &traitement::traitementFindObjet, mat_current);

}

void MainWindow::demarrageTraiForme(){

    t1 = QtConcurrent::run(&this->_Traitement, &traitement::traitementForme, mat_current);

}

///Affiche les résultats en sortie du traitement
void MainWindow::affichageResComptage(){



    int nbre_objets = -1;
    _Traitement.getResultatComptage(nbre_objets);

    QString _msgInfp;
    _msgInfp.append("Nombre d'objets détéctés : ");
    _msgInfp.append(QString::number(nbre_objets));
    ui->layout_res->addWidget(res);
    res->setInfos(_msgInfp);
    res->setInfosComptageObjet(_Traitement.getResultatComptage());

    cv::Mat mat_display  = _Traitement.getMatCurrent(); //Recupere l'image traitée

    mat_label =  _Traitement.getMatLabel();
    _bdisplayRescomptage = true;

    displayImageRes(mat_display); //Affichage de l'image en sortie du traitement
  //  qApp->setActiveWindow(this); //Mets la fenetre de résultat en avant plan
}


void MainWindow::displayImageRes(cv::Mat matDisplay){

    QImage im = QImageToMat::cvMatToQImage(matDisplay);
    imageLbl->setScaledContents(true);
    imageLbl->setFixedWidth(im.width());
    imageLbl->setFixedHeight(im.height());
    imageLbl->setPixmap(QPixmap::fromImage(im));
    ui->scrollArea->repaint();
    ui->scrollArea->update();

}


void MainWindow::affichageResCouleurChoix(){


}

void MainWindow::affichageResCouleurDetection(){

}

void MainWindow::affichageResFindObjet(){


}

void MainWindow::affichageResTraiForme(){



}





void MainWindow::slotTraitementFinish()
{
    qDebug() << "Traitement fini";
    ui->pushButton_LED_EtatTraite->setStyleSheet("background-color: green");
    ui->pushButton_LED_EtatTraite->repaint();
    ui->pushButton_LED_EtatTraite->update();

    this->repaint();
    this->update();
    qApp->setActiveWindow(this);
    qDebug() << "End slot finish traitement";

    resultatsTermine();



}


void MainWindow::resultatsTermine(){
    res->show();
    res->setTitleUi(param->getTypeTraitementString());


    E_TYPE_TRAITEMENT typeTraitement =  param->getTypeTraitement();
    qDebug() << param->getTypeTraitementString();

    switch (typeTraitement)
    {
       case COMPTAGE_OBJET:
          affichageResComptage();
          break;
       case CHOIX_COULEUR:
          affichageResCouleurChoix();
          break;
       case DETECTION_COULEUR:
           affichageResCouleurDetection();
           break;
       case RETROUVER_OBJET:
           affichageResFindObjet();
           break;
       case DETECTION_FORME:
           affichageResTraiForme();
           break;
       default:
          QMessageBox::warning(this, tr("Traitement"), tr("Selectionner un mode ! "),  QMessageBox::Cancel, QMessageBox::Ok);
          break;
    }

}


