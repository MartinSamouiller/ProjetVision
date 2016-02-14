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
    QImage * getImageSimulation();
    int  InitCameraBauhmer();
    int  Snap();
    void createMsgError(QString message);

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
   // void on_cbTraitement_currentIndexChanged(const QString &arg1);
   // void on_cbAnalyse_currentIndexChanged(const QString &arg1);
   // void on_actionHistogramme_triggered();
    void on_actionOuvrir_triggered();

    void on_checkBox_Histogramme_clicked();
    //void on_pushButton_clicked();
    int on_pushButton_Live_clicked();
    void on_pushButton_LiveStop_clicked();
    void on_pushButton_Snap_clicked();
    void on_pushButton_Connection_clicked();
    void on_bout_calibrage_clicked();
    void on_apply_reg_clicked();
    void slotInitCameraFiniched();
    void slotSnapFinished();
    void slotInitCameraError();
    void slotRadioButtonMode(bool checked);
    void on_btn_ParametrageMode_clicked();

signals:
    void SelectImage();
    void FinishInit();
    void ErrorInitCamera();

private:
    QImage * imcurrent = NULL;
    cv::Mat mat_current;
    Ui::MainWindow *ui;
    QImage *image_courante;
    std::vector<QImage> images;
    int m_index_image = 0;
    qlabel_image *imageLbl;

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


};

#endif // MAINWINDOW_H
