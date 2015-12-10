#ifndef QLABEL_IMAGE_H
#define QLABEL_IMAGE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

////Classe héritant de QLabel permettant de gerer la lecture des pixels en dynamique (x,y et RGB)
/// Lorsque l'on se déplace sur un qlabel_image, ce widget renvoi la position de la souris en x et y


class qlabel_image : public QLabel
{
    Q_OBJECT
public:
    explicit qlabel_image(QWidget *parent =0);
    ~qlabel_image();
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);

    int x, y;
    int xr, yr;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_ClickLeft();
    void Mouse_ReleasePos();

public slots:


};

#endif // QLABEL_IMAGE_H
