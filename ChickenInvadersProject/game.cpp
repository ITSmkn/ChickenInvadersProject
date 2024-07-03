#include "game.h"
#include "Start_Menu.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

extern Game *game;

Game::Game(int width , int height):Width(width),Height(height){

 SceneSet();

}

void Game::SceneSet(){

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,Width,Height);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(Width ,Height);

}

Game::~Game(){
    delete scene;
}
