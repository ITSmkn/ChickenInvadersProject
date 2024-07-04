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

    ship = new SpaceShip();
    scene->addItem(ship);
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

