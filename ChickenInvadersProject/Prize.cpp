#include "Prize.h"
#include "game.h"

extern Game* game;

Prize::Prize(QTimer* t) : FallingItems(t){
    setPixmap(QPixmap(":/images/src/images/prize.png"));
    connect(time,SIGNAL(timeout()),this,SLOT(MoveDown()));
}

void Prize::MoveDown()
{
    if(y() < game->get_Height()-50)
        setPos(x(),y() + 22);
    else
        delete this;
}

