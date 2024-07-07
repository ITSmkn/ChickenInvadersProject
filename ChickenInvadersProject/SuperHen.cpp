#include "SuperHen.h"
#include "Chicken.h"
#include "game.h"

extern Game* game;

SuperHen::SuperHen(int X, int Y, int r, QTimer* t) : Enemy(X, Y, r, t){
    //setting lives for superhen
    FoeLives = 4;
    setPixmap(QPixmap(":/images/src/images/SuperChicken1.png"));
    connect(time, SIGNAL(timeout()), this, SLOT(wiggle()));
}

void SuperHen::wiggle(){
    if(temp % 2 == 0){
        setPixmap(QPixmap(":/images/src/images/SuperChicken1.png"));
    }
    else{
        setPixmap(QPixmap(":/images/src/images/SuperChicken2.png"));
    }

    ++temp;
}

void SuperHen::decrease_FoeLives(){
    --FoeLives;
    if(FoeLives == 0){
        delete this;
    }
}
