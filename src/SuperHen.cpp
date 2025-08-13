#include "SuperHen.h"
#include "Chicken.h"
#include "game.h"

extern Game* game;

SuperHen::SuperHen(int X, int Y, int r, QTimer* t, QTimer* t2) : Hen(X, Y, r, t, t2){
    //setting lives for superhen
    FoeLives = 4;
    setPixmap(QPixmap(":/images/SuperChicken1.png"));
    connect(time, SIGNAL(timeout()), this, SLOT(SuperHen::wiggle()));
}

void SuperHen::wiggle(){
    if(temp % 2 == 0){
        setPixmap(QPixmap(":/images/SuperChicken1.png"));
    }
    else{
        setPixmap(QPixmap(":/images/SuperChicken2.png"));
    }

    ++temp;
}
