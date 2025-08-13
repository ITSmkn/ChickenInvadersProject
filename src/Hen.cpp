#include "Hen.h"
#include "Chicken.h"
#include "game.h"

extern Game* game;

QVector <Hen*> Hen::hens;

Hen::Hen(int X, int Y, int r, QTimer* t, QTimer* t2) : Enemy(X, Y, r, t), drop_time(t2){
    FoeLives = 2;
    setPixmap(QPixmap(":/images/hen1.png"));
    connect(time, SIGNAL(timeout()), this, SLOT(wiggle()));

}

void Hen::wiggle(){
    if(temp % 2 == 0){
        setPixmap(QPixmap(":/images/hen1.png"));
    }
    else{
        setPixmap(QPixmap(":/images/hen2.png"));
    }

    temp += 1;
}

void Hen::drop_Meat(){
    Meat *meat = new Meat(drop_time);
    meat->setPos(x() , y()+20);
    scene()->addItem(meat);
}

void Hen::drop_Egg(){
    Egg* egg = new Egg(drop_time);
    egg->setPos(x() + 28, y() + 20);//according to the hen's location
    Egg::eggs.append(egg);
    scene()->addItem(egg);
}
