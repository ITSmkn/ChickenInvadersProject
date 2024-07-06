#include "Spaceship.h"
#include "game.h"
#include "Chicken.h"
#include "QDebug"

extern Game *game;

SpaceShip::SpaceShip(QTimer* t):time(t){

    setPixmap(QPixmap(":/images/src/images/SpaceShip.png"));
    setPos(880, 800);
    setFocus();

    connect(time,SIGNAL(timeout()),this,SLOT(detect_collide()));

}

SpaceShip::~SpaceShip(){

}

int SpaceShip::get_lives(){
    return lives;
}

void SpaceShip::set_lives(int n1){
    lives = n1;
}

void SpaceShip::shoot(){

    if(game->isLost == true){   // when we lose shooting will be disabled ...
        return;
    }
    // creating Rocket ...
    if(game->time_count >= 3){// after two seconds you from pushing start button , you can shoot
    rocket = new Rocket(time);
    rocket->setPos(x()+50,y()-110);
    scene()->addItem(rocket);
    }
    // to check if it has hit enemies ...

}


void SpaceShip::detect_collide(){
    // the list which contains colliding items ...
    QList<QGraphicsItem *> collided = collidingItems();

    for(int i = 0 ; i < collided.size() ; i++){
        if(typeid(*collided[i]) == typeid(Chicken)){
            // deleting colliding enemy...
            delete collided[i];
            // decreasing spaceship lives ...
            --lives;
            // we collided ...
            game->isCrashed = true;
            //saving collide time ...
            (game->collide_time) = (game->time_count);
            //change to explosion pic ...
            setPixmap(QPixmap(":/images/src/images/explosion.png"));
            // making the spaceship stand still when crashed...
            game->setMouseTracking(false);

            //check losing ...
            if(lives == 0){
            game->lose();
            }
        }
    }

   //to change lives  ...
   game->check_status();


}
