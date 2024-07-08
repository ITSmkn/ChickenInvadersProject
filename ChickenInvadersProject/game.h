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
#include "Hen.h"
#include "SuperHen.h"
#include "Egg.h"

// this class is actually related to the main game screen

class Game : public QGraphicsView{

    Q_OBJECT

private:

    int Width , Height;
    int level;
    int score;

    QGraphicsScene * scene;

public slots:
    //the function that will be connected to timer(+1 to time_count every 1 sec)...
    void time_counter();

public:

    int enemy_number;

    int time_count;   // to count time...
    int collide_time; // saving time_count whenever spaceship collide...
    int lose_time;
    int levelUp_time;
    int egg_time;

    bool isCrashed ;  // for demonstrating spaceship condition(whether it has collided or ..)...
    bool isLost ;

    // other variable ...

     SpaceShip* ship;
     QTimer* ship_time;
     QTimer* chicken_time;
     QTimer* game_time;
     QTimer* EnemyDrop_time;
     QGraphicsTextItem *lives_board;
     QFont *lives_font;
     QGraphicsTextItem *score_board;
     QFont *score_font;     
     QGraphicsTextItem *levelUp_board;
     QFont *levelUp_font;
     QPushButton* pause;

     // Functions...

     Game(int width , int height);
    ~Game();

     void SceneSet();

     // other functions ...
     int get_Width();
     int get_Height();
     int get_score();

     void set_Width(int w);
     void set_Height(int h);
     void set_score(int s);

     // for shooting ...
     void mousePressEvent(QMouseEvent* event);

     //for ship movement
     void mouseMoveEvent(QMouseEvent *Event);

     //showing spaceship lives(initial setting)
     void show_lives();

     //showing spaceship score(initial setting)
     void show_score();


     void show_LoseBoard();

     void show_levelUpBoard();

     //it will be used when the spaceship collide or kill enemies(to change textitem)
     void check_status();

     //to handle losing
     void lose();

     void addEnemy();
};

#endif // GAME_H
