#ifndef CHOIXCOULEUR_H
#define CHOIXCOULEUR_H

#include <QWidget>

namespace Ui {
class ChoixCouleur;
}

class ChoixCouleur : public QWidget
{
    Q_OBJECT

public:
    explicit ChoixCouleur(QWidget *parent = 0);
    ~ChoixCouleur();

private:
    Ui::ChoixCouleur *ui;
};

#endif // CHOIXCOULEUR_H
