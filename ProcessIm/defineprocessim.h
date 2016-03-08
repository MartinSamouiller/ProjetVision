#ifndef DEFINEPROCESSIM
#define DEFINEPROCESSIM

#include <QColor>

//Different mode de traitement
enum E_TYPE_TRAITEMENT {

    DETECTION_FORME,
    DETECTION_COULEUR,
    CHOIX_COULEUR,
    COMPTAGE_OBJET,
    RETROUVER_OBJET,

};

struct S_INFOS_OBJETS {
  int label;
  float area; //aire
  float radius; //rayon
  QRgb  color;
  QPointF center;

} ;

#endif // DEFINEPROCESSIM

