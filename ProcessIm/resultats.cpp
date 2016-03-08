#include "resultats.h"
#include "ui_resultats.h"

#include <QStandardItemModel>
#include <QtDebug>

Resultats::Resultats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resultats)
{
    ui->setupUi(this);
}

Resultats::~Resultats()
{
    delete ui;
}


void Resultats::setTitleUi(QString title){
    ui->lbl_type->setText(title);
}

QVBoxLayout* Resultats::getLayoutInfos(){
    return ui->layout_tabRes;
}

QHBoxLayout* Resultats::getLayoutTab(){
    return ui->layout_infos;
}

void Resultats::setInfos(QString infos){
    ui->label_infos->setText(infos);
}

void Resultats::setInfosComptageObjet(std::vector<S_INFOS_OBJETS> infos_objets){

    if(infos_objets.empty())
        return;

    QStandardItemModel *model = new QStandardItemModel(infos_objets.size(),5,this); //2 Rows and 3 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Label")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Area")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Radius")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Center")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Color")));

    for(int i = 0; i < infos_objets.size(); i++)
    {
        QPointF ptn = infos_objets[i].center;

        QString sptn = QString("x:%1 / y:%2").arg(QString::number(ptn.x()), QString::number(ptn.y()));
        model->setItem(i,0,new QStandardItem(QString::number(infos_objets[i].label) ));
        model->setItem(i,1,new QStandardItem(QString::number(infos_objets[i].area) ));
        model->setItem(i,2,new QStandardItem(QString::number(infos_objets[i].radius) ));
        model->setItem(i,3,new QStandardItem(sptn));
        model->setItem(i,4,new QStandardItem(QString("no color") ));
    }

    ui->tableView_res->setModel(model);
    ui->tableView_res->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_res->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_res->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_res->selectRow(2);
}

void Resultats::setSelectRowTab(int row){
     ui->tableView_res->selectRow(row);
}

