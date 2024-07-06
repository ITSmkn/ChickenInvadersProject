#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsPixmapItem>
#include "Rocket.h"


class SpaceShip : public QGraphicsPixmapItem{


private:

    int lives = 3;

public:

    SpaceShip(QTimer* t);
    ~SpaceShip();

    Rocket* rocket;
    QTimer* time;

    int get_lives();
    void set_lives(int);
    void shoot();
};

#endif // SPACESHIP_H
