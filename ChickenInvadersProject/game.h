#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>

#include "Spaceship.h"

// this class is actually related to the main game screen

class Game : public QGraphicsView{

private:
    int Width , Height;
    QGraphicsScene * scene;

public:
     SpaceShip *ship;

     Game(int width , int height);
    ~Game();

     void SceneSet();

     // other functions ...
     int get_Width();
     int get_Height();

     void set_Width(int w);
     void set_Height(int h);
};

#endif // GAME_H
