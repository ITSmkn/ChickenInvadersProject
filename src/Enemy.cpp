#include "Enemy.h"
#include "game.h"

extern Game* game;


Enemy::Enemy(int x, int y , int r,QTimer* t):X(x),Y(y),rows(r),time(t){

    temp = 0;
    setPos(x,y);
    connect(time,SIGNAL(timeout()),this,SLOT(MoveDown()));
};

void Enemy::decrease_FoeLives(){
    --FoeLives;
}


int Enemy::get_FoeLives(){
    return FoeLives;
}


void Enemy::MoveDown(){
    if(y() < game->get_Height()*2/3 - (rows+1)*120 - 35){
    setPos(X , y() + 25);
    }
}
