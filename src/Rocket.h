#ifndef ROCKET_H
#define ROCKET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>

#include "Chicken.h"
#include "Hen.h"
#include "SuperHen.h"


class Rocket :public QObject ,public QGraphicsPixmapItem{

    Q_OBJECT

public:

    // timer for the rocket object to move ...
    QTimer * time;

    Rocket(QTimer* t); //constructor gets a QTimer pointer ...

public slots:

    //function for rocket's movement (will be connected to the time) ...
    void move();
};



#endif // ROCKET_H
