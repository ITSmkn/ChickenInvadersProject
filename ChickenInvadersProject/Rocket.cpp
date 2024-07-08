#include "Rocket.h"
#include "game.h"
#include "Meat.h"

extern Game* game; // it should be here because the move function that we defined ...

Rocket::Rocket(QTimer* t):time(t){

    // setting pic on the rocket ...
    setPixmap(QPixmap(":/images/src/images/Rocket.png"));

    //connecting the function move to time vlaue ...
    connect(time,SIGNAL(timeout()),this,SLOT(move()));
}


void Rocket::move(){
    //collidingitems() is a list of collided QGraphicsitems
    QList<QGraphicsItem*> collided = collidingItems();

    for(int i = 0; i < collided.size(); i++){
        //checking the type
        //for chicken
        if(typeid (Chicken) == typeid (*collided[i])){
            //deleting the rocket while it hits an enemy
            delete this;

            //decreasing the number of enemies...
            game->enemy_number -= 1;
            if(game->enemy_number == 0){
               game->levelUp_time = game->time_count;
            }

            //updating the score
            int z = game->get_score();
            game->set_score(z + 5);

            // updating status ...
            game->check_status();

            // casting QGraphicsItem to Chicken to use class's function
            Chicken *temp = dynamic_cast<Chicken*>(collided[i]);
            temp->decrease_FoeLives();
            // deleting the chicken
            delete collided[i];
            return;
        }

        //for hen
        else if(typeid (Hen) == typeid (*collided[i])){
            //deleting the rocket when it hits an enemy
            delete this;

            // casting QGraphicsItem to Chicken to use class's function
            Hen *temp = dynamic_cast<Hen*>(collided[i]);
            temp->decrease_FoeLives();

            if(temp->get_FoeLives() == 0){
                //updating the score
                int z = game->get_score();
                game->set_score(z + 10);

                // updating status ...
                game->check_status();

                //decreasing the number of enemies...
                game->enemy_number -= 1;
                if(game->enemy_number == 0){
                   game->levelUp_time = game->time_count;
                }

                Hen::hens.remove(Hen::hens.indexOf(static_cast<Hen*>(collided[i])));
                  temp->drop_Meat();
                delete collided[i];
            }
                return;
        }

        //for superhen
        else if(typeid (SuperHen) == typeid (*collided[i])){
            //deleting the rocket while it hits an enemy
            delete this;

            // casting QGraphicsItem to Chicken to use class's function
            SuperHen *temp = dynamic_cast<SuperHen*>(collided[i]);
            temp->decrease_FoeLives();

            if(temp->get_FoeLives() == 0){
                //updating the score
                int z = game->get_score();
                game->set_score(z + 20);

                // updating status ...
                game->check_status();

                //decreasing the number of enemies...
                game->enemy_number -= 1;
                if(game->enemy_number == 0){
                   game->levelUp_time = game->time_count;
                }

                Hen::hens.remove(Hen::hens.indexOf(dynamic_cast<SuperHen *>(collided[i])));
                temp->drop_Meat();
                delete collided[i];
            }

            return;

        }

        else if (typeid((*collided[i])) == typeid(Egg)) {
            // deleting rocket
            delete this;
            // increasing the score
            int z = game->get_score();
            game->set_score(z + 5);
            // updating status ...
            game->check_status();
            //deleting from egg list
            Egg::eggs.remove(Egg::eggs.indexOf(static_cast<Egg *>(collided[i])));
            delete collided[i];

            return;
        }



    }


    //these x() and y() are the position of the rocket in the game view ...
    if(y() > 0){
        setPos(x(),y() - 50);
    }

    else{
        scene()->removeItem(this);
        delete this;
    }
    // updating status ...
    game->check_status();


}
