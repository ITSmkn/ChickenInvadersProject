#include "Chicken.h"
#include "game.h"

extern Game* game;


Chicken::Chicken(int X, int Y , int r,QTimer* t) : Enemy(X, Y, r ,t){

    // setting lives for chicken ...
    FoeLives = 1;
    setPixmap(QPixmap(":/images/chicken1.png"));
    connect(time,SIGNAL(timeout()),this,SLOT(wiggle()));
}

void Chicken::wiggle(){

    // as this method works over and over again by our time value , we can use these conditions ...
    if(temp %2 == 0){
        setPixmap(QPixmap(":/images/chicken1.png"));
    }

    else{
        setPixmap(QPixmap(":/images/chicken2.png"));
    }

    temp += 1;

}

