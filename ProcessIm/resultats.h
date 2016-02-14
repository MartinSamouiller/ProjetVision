#ifndef RESULTATS_H
#define RESULTATS_H

#include <QWidget>

namespace Ui {
class Resultats;
}

class Resultats : public QWidget
{
    Q_OBJECT

public:
    explicit Resultats(QWidget *parent = 0);
    ~Resultats();

private:
    Ui::Resultats *ui;
};

#endif // RESULTATS_H
