#ifndef DETECTIONCOULEURS_H
#define DETECTIONCOULEURS_H

#include <QWidget>

namespace Ui {
class DetectionCouleurs;
}

class DetectionCouleurs : public QWidget
{
    Q_OBJECT

public:
    explicit DetectionCouleurs(QWidget *parent = 0);
    ~DetectionCouleurs();

private:
    Ui::DetectionCouleurs *ui;
};

#endif // DETECTIONCOULEURS_H
