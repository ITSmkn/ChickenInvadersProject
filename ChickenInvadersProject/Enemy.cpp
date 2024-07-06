#include "Enemy.h"


Enemy::Enemy(int n1, int n2 , QTimer* t):x(n1),y(n2),time(t) {

    temp = 0;
};


int Enemy::get_FoeLives(){
    return FoeLives;
}
