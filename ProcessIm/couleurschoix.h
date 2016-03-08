#ifndef COULEURSCHOIX_H
#define COULEURSCHOIX_H

#include <QWidget>

namespace Ui {
class CouleursChoix;
}

class CouleursChoix : public QWidget
{
    Q_OBJECT

public:
    explicit CouleursChoix(QWidget *parent = 0);
    ~CouleursChoix();
    void getRGBIntervalle(int& R, int& B, int& G, int& intervalle);
    void getRGBIntervalle(QColor& color, int& intervalle);
    void setTitle(QString title);

private slots:
    void on_pushButton_clicked();
    void slotColor(QColor);

private:
    Ui::CouleursChoix *ui;
    QColor _color;
};

#endif // COULEURSCHOIX_H
