#include "Spaceship.h"
#include "game.h"
#include "QDebug"

extern Game *game;

SpaceShip::SpaceShip(QTimer* t):time(t){

    setPixmap(QPixmap(":/images/src/images/SpaceShip.png"));
    setPos(880, 800);

}

SpaceShip::~SpaceShip(){

}

int SpaceShip::get_lives()
{
    return lives;
}

void SpaceShip::set_lives(int n1){
    lives = n1;
}

void SpaceShip::shoot(){

    // creating Rocket ...

    rocket = new Rocket(time);
    rocket->setPos(x()+45,y()-150);

    scene()->addItem(rocket);
}

