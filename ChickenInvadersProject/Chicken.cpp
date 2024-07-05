#include "Chicken.h"


Chicken::Chicken(int X, int Y , QTimer* t) : Enemy(X, Y, t){

    // setting lives for chicken ...
    FoeLives = 1;

    setPixmap(QPixmap(":/images/src/images/chicken1.png"));
    setPos(X, Y);
    connect(time,SIGNAL(timeout()),this,SLOT(wiggle()));
}

void Chicken::wiggle(){

    // as this method works over and over again by our time value , we can use these conditions ...
    if(temp %2 == 0){
        setPixmap(QPixmap(":/images/src/images/chicken1.png"));
    }

    else{
        setPixmap(QPixmap(":/images/src/images/chicken2.png"));
    }

    temp += 1;

}
