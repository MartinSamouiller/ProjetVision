#ifndef RESULTATS_H
#define RESULTATS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "defineprocessim.h"

namespace Ui {
class Resultats;
}

class Resultats : public QWidget
{
    Q_OBJECT

public:
    explicit Resultats(QWidget *parent = 0);
    ~Resultats();
    void setTitleUi(QString title);
    QHBoxLayout* getLayoutTab();
    QVBoxLayout* getLayoutInfos();
    void setInfos(QString infos);
    void setInfosComptageObjet(std::vector<S_INFOS_OBJETS> infos_objets);
    void setSelectRowTab(int row);

private:
    Ui::Resultats *ui;
};

#endif // RESULTATS_H
