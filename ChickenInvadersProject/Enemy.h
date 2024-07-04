#ifndef ENEMY_H
#define ENEMY_H

#include "QGraphicsPixmapItem"

class Enemy : public QGraphicsPixmapItem{
protected:
    int x, y;

public:
    Enemy(int n1, int n2);
    ~Enemy();

};

#endif // ENEMY_H
