#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QBoxLayout>
#include <QImage>

#include "qlabel_image.h"

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



signals:
    void SelectImage();

private:
    Ui::MainWindow *ui;
    QImage *image_courante;
    std::vector<QImage> images;
    int m_index_image = 0;
    qlabel_image *imageLbl;
    //QBoxLayout *Layout_Travail;


};

#endif // MAINWINDOW_H
