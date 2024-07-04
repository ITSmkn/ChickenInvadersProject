#include "Rocket.h"
#include "game.h"

extern Game* game; // it should be here because the move function that we defined ...

Rocket::Rocket(QTimer* t):time(t){

    // setting pic on the rocket ...
    setPixmap(QPixmap(":/images/src/images/Rocket.png"));

    //connecting the function move to time vlaue ...
    connect(time,SIGNAL(timeout()),this,SLOT(move()));

}


void Rocket::move(){

}
