#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QMouseEvent>
#include <QPushButton>

#include "Spaceship.h"
#include "Chicken.h"
#include "Rocket.h"

// this class is actually related to the main game screen

class Game : public QGraphicsView{

private:
    int Width , Height;
    QGraphicsScene * scene;

public:

     SpaceShip *ship;
     QTimer *ship_time;
     QPushButton  *pause ;

     Game(int width , int height);
    ~Game();

     void SceneSet();

     // other functions ...
     int get_Width();
     int get_Height();

     void set_Width(int w);
     void set_Height(int h);

     // for shooting ...
     void mousePressEvent(QMouseEvent* event);

     //for ship movement
     void mouseMoveEvent(QMouseEvent *Event);
};

#endif // GAME_H
