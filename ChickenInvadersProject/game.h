#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsSimpleTextItem>
#include <QFont>

#include "Spaceship.h"
#include "Enemy.h"
#include "Chicken.h"
#include "Rocket.h"

// this class is actually related to the main game screen

class Game : public QGraphicsView{
    Q_OBJECT
private:
    int Width , Height;
    int level;
    QGraphicsScene * scene;

public:

     SpaceShip* ship;
     QTimer* ship_time;
     QTimer* chicken_time;
     QGraphicsTextItem *lives_board;
     QFont *lives_font;
     QPushButton* pause;

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

     //showing spaceship lives(initial setting)
     void show_lives();

     //it will be used when the spaceship collide or kill enemies(to change textitem)
     void check_status();
};

#endif // GAME_H
