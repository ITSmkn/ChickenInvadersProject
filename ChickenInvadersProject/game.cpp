#include "game.h"
#include "Start_Menu.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

extern Game *game;

Game::Game(int width , int height):Width(width),Height(height),score(0){

    level = 1;
    time_count = 0;
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
    delete levelUp_board;
    delete levelUp_font;

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

    //setting background to the main game screen according to the level ...
    if(level < 3){
    setBackgroundBrush(QPixmap(":/images/src/images/Level1Bg.png"));
    }
    else{
    setBackgroundBrush(QPixmap(":/images/src/images/Level2Bg.png"));
    }

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

    addEnemy();
    //setting font
    lives_font = new QFont("Arial", 25);
    lives_font->setBold(true);

    score_font = new QFont("Arial", 30);
    score_font->setBold(true);

    levelUp_font = new QFont("Arial", 40);
    levelUp_font->setBold(true);
    levelUp_font->setItalic(true);

    //setting boards
    show_lives();
    scene->addItem(lives_board);

    show_score();
    scene->addItem(score_board);

    //cursor tracker was enabled
    setMouseTracking(true);
    setFocus();

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

    // level up ...
    if(enemy_number == 0){
    ship->setPos(880,800);
    show_levelUpBoard();
    scene->addItem(levelUp_board);
    if((time_count - 4) == levelUp_time){

    if(level == 6){                      // to check victory
        Start_menu *sm = new Start_menu();
        sm->show();
        game->close();
    }
    else{
    time_count= 0;
    ++level;
    int n = ship->get_lives(); // keep the lives for the remaining levels
    SceneSet();                // lives = 3
    ship->set_lives(n);        // but the former lives will be set on it

    // if lives = 1 and you collide the last enemy in a particular level
    if(ship->get_lives() == 0){
        Start_menu *sm = new Start_menu();
        sm->show();
        game->close();
    }
    }
    }
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

void Game::show_levelUpBoard(){
    levelUp_board = new QGraphicsTextItem;
    levelUp_board->setPos(100,500);
    levelUp_board->setFont(*levelUp_font);
    levelUp_board->setDefaultTextColor(Qt::white);
    if(level == 1){
        levelUp_board->setPlainText(QString("Congrats ! you just passed level 1 of season 1"));
    }
    if(level == 2){
        levelUp_board->setPlainText(QString("Congrats ! you just passed level 2 of season 1"));
    }
    if(level == 3){
        levelUp_board->setPlainText(QString("Congrats ! you just passed level 1 of season 2"));
    }
    if(level == 4){
        levelUp_board->setPlainText(QString("Congrats ! you just passed level 2 of season 2"));
    }
    if(level == 5){
        levelUp_board->setPlainText(QString("Congrats ! you just passed level 1 of season 3"));
    }
    if(level == 6){
        QPixmap image(":/images/src/images/win.png");
        QGraphicsPixmapItem* win_pic = new QGraphicsPixmapItem(image);
        win_pic->setPos(560,100);
        scene->addItem(win_pic);
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



void Game::addEnemy(){

    if(level == 1){
        enemy_number = 20;
        for(int i = 0 ; i <= 3 ; i++){ // rows
            for(int j = 0 ; j <= 4 ; j++){
                auto chicken = new Chicken(550 + j*170 , -i*120 , i , chicken_time);
                scene->addItem(chicken);
            }
        }
    }

    if(level == 2){
        enemy_number = 36;
        for(int i = 0 ; i <= 3 ; i++){ // rows
            for(int j = 0 ; j <= 8 ; j++){
                auto chicken = new Chicken(275 + j*170 , -i*120 , i , chicken_time);
                scene->addItem(chicken);
            }
        }
    }

    if(level == 3){
        enemy_number = 24;
        for(int i = 0 ; i <= 2 ; i++){ // rows
            for(int j = 0 ; j <= 7 ; j++){
                if(j%2 == 0){
                auto chicken = new Chicken(300 + j*170 , -i*120 , i , chicken_time);
                scene->addItem(chicken);
                }
                else{
                    auto chicken = new Hen(300 + j*170 , -i*120 , i , chicken_time);
                    scene->addItem(chicken);
                }
            }
        }
    }

    if(level == 4){
        enemy_number = 30;
        for(int i = 0 ; i <= 2 ; i++){ // rows
            for(int j = 0 ; j <= 9 ; j++){
                if(j%3 == 0){
                auto chicken = new Chicken(180 + j*170 , -i*120 , i , chicken_time);
                scene->addItem(chicken);
                }
                else{
                    auto chicken = new Hen(180 + j*170 , -i*120 , i , chicken_time);
                    scene->addItem(chicken);
                }
            }
        }
    }

    if(level == 5){
        enemy_number = 18;
        for(int i = 0 ; i <= 2 ; i++){ // rows
            for(int j = 0 ; j <= 5 ; j++){
                if(j%2 == 0){
                auto chicken = new Hen(500 + j*170 , -i*120 , i , chicken_time);
                scene->addItem(chicken);
                }
                else{
                    auto chicken = new SuperHen(500 + j*170 , -i*120 , i , chicken_time);
                    scene->addItem(chicken);
                }
            }
        }
    }

    if(level == 6){
        enemy_number = 27;
        for(int i = 0 ; i <= 2 ; i++){ // rows
            for(int j = 0 ; j <= 8 ; j++){
                auto chicken = new SuperHen(275 + j*170 , -i*130 , i , chicken_time);
                scene->addItem(chicken);
            }
        }
    }

}
