#ifndef COMPTAGEOBJET_H
#define COMPTAGEOBJET_H

#include <QWidget>

namespace Ui {
class ComptageObjet;
}

class ComptageObjet : public QWidget
{
    Q_OBJECT

public:
    explicit ComptageObjet(QWidget *parent = 0);
    ~ComptageObjet();
    bool getHSV(){return _hsv; };
    int getThreshold(){return _threshold; };
    int getSizeMorpho(){return _sizeMorpho; };

private slots:
    void on_checkBox_HSV_clicked();
    void on_spinBox_Threshold_valueChanged(int arg1);
    void on_spinBox_OpenSize_valueChanged(int arg1);

private:
    Ui::ComptageObjet *ui;
    bool _hsv;
    int _threshold;
    int _sizeMorpho;
};

#endif // COMPTAGEOBJET_H
