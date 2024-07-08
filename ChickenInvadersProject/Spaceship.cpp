#include "Spaceship.h"
#include "game.h"
#include "Chicken.h"
#include "QDebug"

extern Game *game;

SpaceShip::SpaceShip(QTimer* t):time(t){

    setPixmap(QPixmap(":/images/src/images/SpaceShip.png"));
    setPos(880, 800);
    setFocus();
    DoubleShot = false;
    connect(time,SIGNAL(timeout()),this,SLOT(detect_collide()));

}

SpaceShip::~SpaceShip(){}

int SpaceShip::get_lives(){
    return lives;
}

void SpaceShip::set_lives(int n1){
    lives = n1;
}

void SpaceShip::shoot(){

    if(game->isLost == true || game->isCrashed == true){   // when we lose shooting will be disabled ...
        return;
    }
    if(DoubleShot == false){
    // creating Rocket ...
    if(game->time_count >= 3){// after seconds you from pushing start button , you can shoot
    rocket = new Rocket(time);
    rocket->setPos(x()+50,y()-110);
    scene()->addItem(rocket);
    }
    }
    else{

        rocket = new Rocket(time);
        rocket->setPos(x()+30,y()-110);
        scene()->addItem(rocket);

        rocket = new Rocket(time);
        rocket->setPos(x()+65,y()-110);
        scene()->addItem(rocket);
    }

}


void SpaceShip::detect_collide(){
    // the list which contains colliding items ...
    QList<QGraphicsItem *> collided = collidingItems();

    for(int i = 0 ; i < collided.size() ; i++){
        //checking the type
        if(typeid(*collided[i]) == typeid(Chicken) || typeid (*collided[i]) == typeid (Hen)
                || typeid (*collided[i]) == typeid (SuperHen)){


            // deleting from our egg droping vector
            if(typeid((*collided[i])) == typeid(Hen)){
                Hen::hens.remove(Hen::hens.indexOf(dynamic_cast<Hen *>(collided[i])));
            }
            else if(typeid((*collided[i])) == typeid(SuperHen)){
                Hen::hens.remove(Hen::hens.indexOf(dynamic_cast<SuperHen *>(collided[i])));
            }

            // deleting colliding enemy...
            delete collided[i];

            //decreasing the number of enemies...
            game->enemy_number -= 1;
            if(game->enemy_number == 0){           // for showing levelUp_board
                 game->levelUp_time = game->time_count;
            }

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

        else if(typeid(*(collided[i])) == typeid(Prize)){
            DoubleShot = true; // changing shoot mode to 2
            delete collided[i];
        }

        else if(typeid(*(collided[i])) == typeid(Egg)){
            --lives;
            Egg::eggs.remove(Egg::eggs.indexOf(static_cast<Egg *>(collided[i])));
            delete collided[i];
            // for checking in time_counter function ...
            game->isCrashed = true;
            (game->collide_time) = (game->time_count);
            setPixmap(QPixmap(":/images/src/images/explosion.png"));

            game->setMouseTracking(false);
            // check losing ...
            if(lives ==0){
               game->lose();
            }
        }

        else if(typeid(*(collided[i])) == typeid(Meat)){
            delete collided[i];
            (game->meat_number) += 1;
            // when the number of meats goes more than 30 ...
            if(game->meat_number >= 30){
                game->meat_number -= 30;
                int z = game->get_score();
                game->set_score(z+50);
            }
        }
    }

   //to change lives  ...
   game->check_status();
}
