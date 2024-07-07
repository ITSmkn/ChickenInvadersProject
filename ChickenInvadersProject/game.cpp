#include "game.h"
#include "Start_Menu.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

extern Game *game;

Game::Game(int width , int height):Width(width),Height(height),score(0){
    isCrashed = false;
    isLost = false;

 SceneSet();

 game_time = new QTimer;   //the begining of time counter ...
 connect(game_time,SIGNAL(timeout()),this,SLOT(time_counter()));
 game_time->start(1000);

}

Game::~Game(){

    delete scene;
    delete ship;
    delete ship_time;
    delete chicken_time;
    delete lives_board;
    delete lives_font;
    delete score_board;
    delete score_font;
    delete game_time;

}


void Game::SceneSet(){
    if(isLost == false){
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
    chicken_time = new QTimer;

    // these timers make their connected functions work every (n) ms ...
    // giving value to them ...
    ship_time->start(45);
    chicken_time->start(125);

    ship = new SpaceShip(ship_time);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();

    scene->addItem(ship);


    //setting font
    lives_font = new QFont("Arial", 25);
    lives_font->setBold(true);

    score_font = new QFont("Arial", 30);
    score_font->setBold(true);

    //setting boards
    show_lives();
    scene->addItem(lives_board);

    show_score();
    scene->addItem(score_board);

    //cursor tracker was enabled
    setMouseTracking(true);
    setFocus();


    auto hen1 = new Hen(620, -360, 3, chicken_time);
    scene->addItem(hen1);

    auto hen2 = new Hen(760, -360, 3, chicken_time);
    scene->addItem(hen2);

    auto hen3 = new Hen(900, -360, 3, chicken_time);
    scene->addItem(hen3);

    auto hen4 = new Hen(1040, -360, 3, chicken_time);
    scene->addItem(hen4);

    auto hen5 = new Hen(1180, -360, 3, chicken_time);
    scene->addItem(hen5);

    auto superhen1 = new SuperHen(620, -240, 2, chicken_time);
    scene->addItem(superhen1);

    auto superhen2 = new SuperHen(760, -240, 2, chicken_time);
    scene->addItem(superhen2);

    auto superhen3 = new SuperHen(900, -240, 2, chicken_time);
    scene->addItem(superhen3);

    auto superhen4 = new SuperHen(1040, -240, 2, chicken_time);
    scene->addItem(superhen4);

    auto superhen5 = new SuperHen(1180, -240, 2, chicken_time);
    scene->addItem(superhen5);

    auto chicken1 = new Chicken(620, -120, 1, chicken_time);
    scene->addItem(chicken1);

    auto chicken2 = new Chicken(760, -120, 1, chicken_time);
    scene->addItem(chicken2);

    auto chicken3 = new Chicken(900, -120, 1, chicken_time);
    scene->addItem(chicken3);

    auto chicken4 = new Chicken(1040, -120, 1, chicken_time);
    scene->addItem(chicken4);

    auto chicken5 = new Chicken(1180, -120, 1, chicken_time);
    scene->addItem(chicken5);

    auto chicken16 = new Chicken(620, 0, 0,chicken_time);
    scene->addItem(chicken16);

    auto chicken17 = new Chicken(760, 0, 0,chicken_time);
    scene->addItem(chicken17);

    auto chicken18 = new Chicken(900, 0, 0,chicken_time);
    scene->addItem(chicken18);

    auto chicken19 = new Chicken(1040, 0, 0,chicken_time);
    scene->addItem(chicken19);

    auto chicken20 = new Chicken(1180, 0, 0,chicken_time);
    scene->addItem(chicken20);



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
    else{
    // handle losing ...
    show_LoseBoard();
    }
}

//getters
int Game::get_Width(){
    return Width;
}

int Game::get_Height(){
    return Height;
}

int Game::get_score(){
    return score;
}

//setters
void Game::set_Width(int w){
    Width = w;
}

void Game::set_Height(int h){
    Height = h;
}

void Game::set_score(int s){
    score = s;
}

//other methods



void Game::time_counter(){

    // increasing our counter ...
    ++time_count;

    // returning to main menu due to losing ...
    if(lose_time + 4 == time_count && isLost){
        Start_menu *sm = new Start_menu();
        sm->show();
        game->close();
    }

    // setting spaceship's condition to default (after crashing) ...
    if(collide_time == (time_count -2) && isCrashed == true){
       ship->setPixmap(QPixmap(":/images/src/images/SpaceShip.png"));
       ship->setPos(880,800);
       setMouseTracking(true);
       isCrashed = false;
    }

}


void Game::mousePressEvent(QMouseEvent* event){

    if (event->button() == Qt::LeftButton){
         ship->shoot();
     }
}

void Game::mouseMoveEvent(QMouseEvent *event){
    ship->setPos(event->x(), event->y()-35);
}

void Game::lose()
{
    isLost = true;
    lose_time = time_count;
    SceneSet();              // it turns back to set scene and shows lost board ...
    ship->hide();
    lives_board -> hide();
}

void Game::show_LoseBoard(){
    if(isLost){
        QPixmap image(":/images/src/images/lose.png");
        QGraphicsPixmapItem* lose_pic = new QGraphicsPixmapItem(image);
        lose_pic->setPos(500,470);
        scene->addItem(lose_pic);
    }
}

void Game::show_lives(){
    lives_board = new QGraphicsTextItem;
    lives_board->setPlainText(QString::number(ship->get_lives()));
    lives_board->setPos(90, 930);
    lives_board->setDefaultTextColor(Qt::red);
    lives_board->setFont(*lives_font);
}

void Game::show_score(){
    score_board = new QGraphicsTextItem;
    score_board->setPlainText(QString::number(score));
    score_board->setPos(110, 5);
    score_board->setDefaultTextColor(Qt::yellow);
    score_board->setFont(*score_font);
}

void Game::check_status(){
    //setplaintext() is for when you want to update a text
    lives_board->setPlainText(QString::number(ship->get_lives()));

    score_board->setPlainText(QString::number(score));
}
