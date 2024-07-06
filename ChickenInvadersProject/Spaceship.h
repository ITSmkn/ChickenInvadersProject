#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QObject>
#include <QMouseEvent>

#include "Rocket.h"


class SpaceShip :public QObject,public QGraphicsPixmapItem{

    Q_OBJECT
private:

    int lives = 1;

public:

    SpaceShip(QTimer* t);
    ~SpaceShip();

    Rocket* rocket;
    QTimer* time;

    int get_lives();
    void set_lives(int);
    void shoot();

public slots:
    void detect_collide();
};

#endif // SPACESHIP_H
