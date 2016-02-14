#ifndef RETROUVEROBJET_H
#define RETROUVEROBJET_H

#include <QWidget>

namespace Ui {
class RetrouverObjet;
}

class RetrouverObjet : public QWidget
{
    Q_OBJECT

public:
    explicit RetrouverObjet(QWidget *parent = 0);
    ~RetrouverObjet();

private:
    Ui::RetrouverObjet *ui;
};

#endif // RETROUVEROBJET_H
