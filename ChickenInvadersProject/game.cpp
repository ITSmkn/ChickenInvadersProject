#include "game.h"
#include "Start_Menu.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

extern Game *game;

Game::Game(int width , int height):Width(width),Height(height){

 SceneSet();

}

Game::~Game(){
    delete scene;
    delete ship;
    delete ship_time;
}


void Game::SceneSet(){

    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,Width,Height);
    setFixedSize(Width ,Height);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //fullscreen...
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    //setting background to the main game screen
    setBackgroundBrush(QPixmap(":/images/src/images/Level1Bg.png"));

    //removing the cursor
    QCursor csr(Qt::BlankCursor);
    setCursor(csr);

    ship_time = new QTimer;

    ship = new SpaceShip(ship_time);
    scene->addItem(ship);

    //cursor tracker was enabled
    setMouseTracking(true);
    setFocus();

    auto chicken = new Chicken(880, 500);
    scene->addItem(chicken);

    // these timers make their connected functions work every (n) ms...
    ship_time->start(45);
}

int Game::get_Width(){
    return Width;
}

int Game::get_Height(){
    return Height;
}

void Game::set_Width(int w){
    Width = w;
}

void Game::set_Height(int h){
    Height = h;
}

void Game::mousePressEvent(QMouseEvent* event){

    if (event->button() == Qt::LeftButton){
         ship->shoot();
     }
}

void Game::mouseMoveEvent(QMouseEvent *event){
    ship->setPos(event->x(), event->y()-35);
}
