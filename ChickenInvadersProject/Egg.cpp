#include "Egg.h"
#include "game.h"

extern Game* game;

QVector<Egg*> Egg::eggs;

Egg::Egg(QTimer* t) : FallingItems(t){
    setPixmap(QPixmap(":/images/src/images/egg.png"));
    connect(time,SIGNAL(timeout()),this,SLOT(MoveDown()));
    reached = false;
}

void Egg::MoveDown(){
    if(y() < game->get_Height() - 46){
        setPos(x(), y() + 15);
    }
    else{
        //changing the picture when it reaches the bottom
        setPixmap(QPixmap(":/images/src/images/egg2.png"));
        // saving the time of reaching the bottom to show egg2 png
        game->egg_time = game->time_count;
        reached = true;
    }
}
