#include "Meat.h"
#include "game.h"

extern Game* game;

Meat::Meat(QTimer* t) : FallingItems(t){
    setPixmap(QPixmap(":/images/src/images/meat.png"));
    connect(time,SIGNAL(timeout()),this,SLOT(MoveDown()));
}

void Meat::MoveDown(){

    if(y() < game->get_Height()-20)
        setPos(x(),y() + 28);

    else {
        scene()->removeItem(this);
        delete this;
    }
}
