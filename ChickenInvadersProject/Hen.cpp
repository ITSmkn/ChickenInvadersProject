#include "Hen.h"
#include "Chicken.h"
#include "game.h"

extern Game* game;

Hen::Hen(int X, int Y, int r, QTimer* t) : Enemy(X, Y, r, t){
    FoeLives = 2;
    setPixmap(QPixmap(":/images/src/images/hen1.png"));
    connect(time, SIGNAL(timeout()), this, SLOT(wiggle()));

}

void Hen::wiggle(){
    if(temp % 2 == 0){
        setPixmap(QPixmap(":/images/src/images/hen1.png"));
    }
    else{
        setPixmap(QPixmap(":/images/src/images/hen2.png"));
    }

    temp += 1;
}

void Hen::decrease_FoeLives(){ // droping meat will be added

    --FoeLives;
    if(FoeLives == 0){
        delete this;
    }
}
