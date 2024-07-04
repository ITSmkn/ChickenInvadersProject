#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsPixmapItem>

class SpaceShip : public QGraphicsPixmapItem{
private:
    int lives;

public:

    SpaceShip();
    ~SpaceShip();

};

#endif // SPACESHIP_H
