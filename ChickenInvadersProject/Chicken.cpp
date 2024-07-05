#include "Chicken.h"
#include "game.h"

Chicken::Chicken(int X, int Y) : Enemy(X, Y){
    setPixmap(QPixmap(":/images/src/images/chicken1.png"));
    setPos(X, Y);
}
