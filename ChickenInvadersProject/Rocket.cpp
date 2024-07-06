#include "Rocket.h"
#include "game.h"
#include "Chicken.h"

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
        if(typeid (Chicken) == typeid (*collided[i])){
            //deleting the rocket while it hits an enemy
            delete this;

            //updating the score
            int z = game->get_score();
            game->set_score(z + 5);

            // casting QGraphicsItem to Chicken to use class's function
            Chicken *temp = dynamic_cast<Chicken*>(collided[i]);
            temp->decrease_FoeLives();
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
}
