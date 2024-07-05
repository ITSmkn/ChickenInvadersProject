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

    auto chicken1 = new Chicken(620, 100);
    scene->addItem(chicken1);

    auto chicken2 = new Chicken(760, 100);
    scene->addItem(chicken2);

    auto chicken3 = new Chicken(900, 100);
    scene->addItem(chicken3);

    auto chicken4 = new Chicken(1040, 100);
    scene->addItem(chicken4);

    auto chicken5 = new Chicken(1180, 100);
    scene->addItem(chicken5);

    auto chicken6 = new Chicken(620, 220);
    scene->addItem(chicken6);

    auto chicken7 = new Chicken(760, 220);
    scene->addItem(chicken7);

    auto chicken8 = new Chicken(900, 220);
    scene->addItem(chicken8);

    auto chicken9 = new Chicken(1040, 220);
    scene->addItem(chicken9);

    auto chicken10 = new Chicken(1180, 220);
    scene->addItem(chicken10);

    auto chicken11 = new Chicken(620, 340);
    scene->addItem(chicken11);

    auto chicken12 = new Chicken(760, 340);
    scene->addItem(chicken12);

    auto chicken13 = new Chicken(900, 340);
    scene->addItem(chicken13);

    auto chicken14 = new Chicken(1040, 340);
    scene->addItem(chicken14);

    auto chicken15 = new Chicken(1180, 340);
    scene->addItem(chicken15);

    auto chicken16 = new Chicken(620, 460);
    scene->addItem(chicken16);

    auto chicken17 = new Chicken(760, 460);
    scene->addItem(chicken17);

    auto chicken18 = new Chicken(900, 460);
    scene->addItem(chicken18);

    auto chicken19 = new Chicken(1040, 460);
    scene->addItem(chicken19);

    auto chicken20 = new Chicken(1180, 460);
    scene->addItem(chicken20);

    // these timers make their connected functions work every (n) ms...
    ship_time->start(45);

    //make pause button
    pause = new QPushButton( "| |" , this);
    pause->setGeometry(x() + 1830, y()*2 + 10 , 80 , 80);
    scene->addWidget(pause);
    pause->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    //connect(pause , &QPushButton::clicked , this , &SceneSet::pause_game);

    setStyleSheet("QPushButton{background-color: rgba(244, 40, 11, 180);"
                  "color:rgb(255, 255, 255);"
                  "border-bottom-left-radius:35;"
                  "font: 63 28pt \"Bw Stretch Medium\";"
                  "border:0.5px solid rgb(255, 255, 255);}"
                  "QPushButton:hover{background-color: rgba(29, 61, 239, 220);}"
                  "QPushButton:pressed{background-color: rgba(0, 0, 64, 200);}");
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
