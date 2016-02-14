#ifndef DETECTIONFORME_H
#define DETECTIONFORME_H

#include <QWidget>

namespace Ui {
class DetectionForme;
}

class DetectionForme : public QWidget
{
    Q_OBJECT

public:
    explicit DetectionForme(QWidget *parent = 0);
    ~DetectionForme();

private:
    Ui::DetectionForme *ui;
};

#endif // DETECTIONFORME_H
