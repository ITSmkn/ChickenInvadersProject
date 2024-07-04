#include "Spaceship.h"
#include "game.h"
#include "QDebug"

extern Game *game;

SpaceShip::SpaceShip(){
    setPixmap(QPixmap(":/images/src/images/SpaceShip.png"));
    setPos(880, 800);
}

SpaceShip::~SpaceShip(){

}
