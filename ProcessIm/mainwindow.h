#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QImage>

#include "qlabel_image.h"
#include "traitement.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "bgapi2_genicam.hpp"
#include "bgapi2_def.h"
#include "bgapi2_featurenames.h"

#include "parametragetraitement.h"
#include "resultats.h"

////Page principale de l'application
/// Permet d'acceder a tous les traitements
/// La Mdi Area permet d'afficher les IHM qui contiennent les Images à traiter



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    //QImage * getImageSimulation();
    int  InitCameraBauhmer();
    int  Snap();
    void createMsgError(QString message);
    void resultatsTermine();
    void demarrageTraiComptage();
    void demarrageTraiCouleurChoix();
    void demarrageTraiCouleurDetection();
    void demarrageTraiFindObjet();
    void demarrageTraiForme();
    void affichageResComptage();
    void affichageResCouleurChoix();
    void affichageResCouleurDetection();
    void affichageResFindObjet();
    void affichageResTraiForme();
    void displayImageRes(cv::Mat matDisplay);

private slots:
    //void on_actionOuvrir_une_image_triggered();
    void on_actionQuitter_triggered();
    void on_actionTutoriel_triggered();
    void on_actionA_propos_de_ProcessIm_triggered();
    void on_actionDossier_de_travail_triggered();
    //
    void Mouse_current_pos();
    void Mouse_pressed();
    void MouseClickLeft();
    void Mouse_release_pos();
    void on_actionOuvrir_triggered();
    void on_checkBox_Histogramme_clicked();
    void on_pushButton_Snap_clicked();
    void on_pushButton_Connection_clicked();
    void on_bout_calibrage_clicked();
    void on_apply_reg_clicked();
    void slotInitCameraFiniched();
    void slotSnapFinished();
    void slotInitCameraError();
    void slotRadioButtonMode(bool checked);
    void on_btn_ParametrageMode_clicked();
    void on_pushButton_Save_clicked();
    void on_pushButton_Detection_clicked();
    void slotDemarerTraitement();
    void slotTraitementFinish();


signals:
    void SelectImage();
    void FinishInit();
    void ErrorInitCamera();

private:

    double _dim_x_pix = 100; // mettre taille en x en pixel
    double _dim_y_pix = 100; // mettre taille en y en pixel
    double _pos_x_pix = 50; // Mettre coord en x en pixel
    double _pos_y_pix = 100; // Mettre coord en y en pixel

    QImage * imcurrent = NULL;
    cv::Mat mat_current;
    cv::Mat mat_label; //image de label (objet entre 0 et n)
    qlabel_image *imageLbl;

    Ui::MainWindow *ui;
    QImage im_Acqui;
    std::vector<QImage> images;
    int m_index_image = 0;


    traitement _Traitement;
    //QBoxLayout *Layout_Travail;
    BGAPI2::SystemList * systemList = NULL;
    BGAPI2::System * pSystem = NULL;
    BGAPI2::String sSystemID;

    BGAPI2::InterfaceList * interfaceList = NULL;
    BGAPI2::Interface * pInterface = NULL;
    BGAPI2::String sInterfaceID;

    BGAPI2::DeviceList * deviceList = NULL;
    BGAPI2::Device * pDevice = NULL;
    BGAPI2::String sDeviceID;

    BGAPI2::DataStreamList * datastreamList = NULL;
    BGAPI2::DataStream * pDataStream = NULL;
    BGAPI2::String sDataStreamID;

    BGAPI2::BufferList * bufferList = NULL;
    BGAPI2::Buffer * pBuffer = NULL;


    //QFUture thread
    QFuture<int> t_connectionCamera;
    QString _msgInit;
    QString _msgSnap;
    QString _msgError;

    //Fenetre de parametra!ge des traitement
    ParametrageTraitement *param;
    Resultats *res;

    QFuture<void> t1;

    bool _bdisplayRescomptage = false;


};

#endif // MAINWINDOW_H
