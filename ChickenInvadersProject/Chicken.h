#ifndef CHICKEN_H
#define CHICKEN_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "Enemy.h"

class Chicken : public Enemy{

    Q_OBJECT
public:

    Chicken(int n1, int n2 , QTimer* t);

public slots:
//     overriding wiggle for Chicken class ...
    void wiggle() override;

};


#endif // CHICKEN_H
