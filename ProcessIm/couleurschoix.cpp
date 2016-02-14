#include "couleurschoix.h"
#include "ui_couleurschoix.h"
#include <QColorDialog>
#include <QtDebug>

CouleursChoix::CouleursChoix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CouleursChoix)
{
    ui->setupUi(this);

}

CouleursChoix::~CouleursChoix()
{
    delete ui;
}

void CouleursChoix::on_pushButton_clicked()
{
    QColorDialog *colordlg =  new QColorDialog();

    QObject::connect(colordlg, SIGNAL(colorSelected(const QColor &)), this, SLOT(slotColor(QColor)));
    QObject::connect(colordlg, SIGNAL(currentColorChanged(const QColor &)), this, SLOT(slotColor(QColor)));

    colordlg->exec();


}

void CouleursChoix::getRGBIntervalle(int& R, int& B, int& G, int& intervalle){
    R = ui->spinBox_R->value();
    B = ui->spinBox_B->value();
    G = ui->spinBox_G->value();
    intervalle = ui->spinBox_Interval->value();
}

void CouleursChoix::slotColor(QColor color){

    ui->spinBox_R->setValue(color.red());
    ui->spinBox_B->setValue(color.blue());
    ui->spinBox_G->setValue(color.green());

    QPalette palette;
    palette.setColor(QPalette::Button, color);
    ui->pushButton->setPalette(palette);
   // qDebug() << "color change";
   // qDebug() << "R : " << QString::number(color.red()) << " G : "  << QString::number(color.green()) << " B " <<  QString::number(color.blue());
}
