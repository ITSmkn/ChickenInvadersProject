#include "game.h"
#include "Start_Menu.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

extern Game *game;

Game::Game(int width , int height):Width(width),Height(height),score(0){

    level = 1;
    meat_number = 0;

    time_count = 0;

    isCrashed = false;
    isLost = false;

    ship_time = new QTimer;
    chicken_time = new QTimer;
    EnemyDrop_time = new QTimer;
    prize_time = new QTimer;

    // these timers make their connected functions work every (n) ms ...
    // giving value to them ...
    ship_time->start(45);
    chicken_time->start(125);
    EnemyDrop_time->start(45);
    prize_time->start(45);


    //setting font
    lives_font = new QFont("Arial", 25);
    lives_font->setBold(true);

    score_font = new QFont("Arial", 30);
    score_font->setBold(true);

    levelUp_font = new QFont("Arial", 40);
    levelUp_font->setBold(true);
    levelUp_font->setItalic(true);

    meat_font = new QFont("Arial", 25);
    meat_font->setBold(true);

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
    delete meat_board;
    delete meat_font;

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
    setBackgroundBrush(QPixmap(":/images/Level1Bg.png"));
    }
    else{
    setBackgroundBrush(QPixmap(":/images/Level2Bg.png"));
    }

    QPixmap image0(":/images/score.png");
    QGraphicsPixmapItem* score_pic = new QGraphicsPixmapItem(image0);
    score_pic->setPos(15,12);
    scene->addItem(score_pic);

    //removing the cursor
    QCursor csr(Qt::BlankCursor);
    setCursor(csr);

    ship = new SpaceShip(ship_time);
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();

    scene->addItem(ship);

    // adding enemies according to the level ...
    addEnemy();

    //setting boards
    show_lives();
    scene->addItem(lives_board);

    show_score();
    scene->addItem(score_board);

    // showing meat board after level 2 ...
    show_meatBoard();
    if(level > 2){
    scene->addItem(meat_board);
    }

    //cursor tracker was enabled
    setMouseTracking(true);
    setFocus();


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

// for pause menu ...

// for resuming the game ...
void Game::resume_game(){

    ship_time->start(45);
    chicken_time->start(125);
    EnemyDrop_time->start(45);
    prize_time->start(45);

    game_time->start(1000);
    // setting cursor on spaceship ...
    QCursor::setPos((ship->x()),(ship->y()));
}

// escape button for pausing the game ...

void Game::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape) {
        // freezing all of the timer ...
        ship_time->stop();
        chicken_time->stop();
        EnemyDrop_time->stop();
        prize_time->stop();

        game_time->stop();
        Start_menu *st = new Start_menu(2);
        st->show();
    }
}


//other methods

void Game::time_counter(){

    // increasing our counter ...
    ++time_count;

    // returning to main menu due to losing ...
    if(lose_time + 4 == time_count && isLost){
        Start_menu *sm = new Start_menu(1);
        sm->show();
        game->close();
    }

    //deleting egg 1 second after reaching the bottom
    for(int i = 0; i < Egg::eggs.size(); i++){
        if(Egg::eggs[i]->reached && game->egg_time + 1 == time_count){
            delete Egg::eggs[i];
            Egg::eggs.removeAt(i);
        }
    }

    // setting spaceship's condition to default (after crashing) ...
    if(collide_time == (time_count -2) && isCrashed == true){
       ship->setPixmap(QPixmap(":/images/SpaceShip.png"));
       ship->setPos(880,800);
       setMouseTracking(true);
       // set the cursor on spaceship
       QCursor::setPos(880,800);
       isCrashed = false;
    }

    // droping prize
    if(time_count == 15 && level > 3 ){
            auto prize = new Prize(prize_time);
            prize->setPos( rand() % Width , 0);   // giving a random location on scene ..
            scene->addItem(prize);
        }

    //choosing 3 different numbers (3/12 = 1/4)
    if(time_count % 5 == 0 && level == 3 && Hen::hens.size() >= 3){
        QVector<int> vec;
        bool b = false;
        while (!b){
            int r1 = rand() % Hen::hens.size();
            int r2 = rand() % Hen::hens.size();
            int r3 = rand() % Hen::hens.size();

            if(r1 != r2 && r1 != r3 && r2 != r3){
                vec.append(r1);
                vec.append(r2);
                vec.append(r3);
                b = true;
            }
        }
        //droping
        for (int i = 0; i <= 2; i++) {
            Hen::hens[vec[i]]->drop_Egg();
        }
    }

    if(time_count % 5 == 0 && (level == 4 || level == 5) && Hen::hens.size() >= 6){
        QVector<int> vec;
        bool b = false;
        while (!b){
            int r1 = rand() % Hen::hens.size();
            int r2 = rand() % Hen::hens.size();
            int r3 = rand() % Hen::hens.size();
            int r4 = rand() % Hen::hens.size();
            int r5 = rand() % Hen::hens.size();
            int r6 = rand() % Hen::hens.size();

            if(r1 != r2 && r1 != r3 && r1 != r4 && r1 != r5 && r1 != r6 && r2 != r3 && r2 != r4 && r2 != r5 && r2 != r6 && r3 != r4 && r3 != r5 && r3 != r6 && r4 != r5 && r4 != r6 && r5 != r6){
                vec.append(r1);
                vec.append(r2);
                vec.append(r3);
                vec.append(r4);
                vec.append(r5);
                vec.append(r6);
                b = true;
            }
        }
        //droping
        for(int i = 0; i <= 5; i++){
            Hen::hens[vec[i]]->drop_Egg();
        }
    }

    if(time_count % 7 == 0 && level == 6 && Hen::hens.size() >= 13){
        QVector<int> vec;
        bool b = false;
        while(!b){
            int r1 = rand() % Hen::hens.size();
            int r2 = rand() % Hen::hens.size();
            int r3 = rand() % Hen::hens.size();
            int r4 = rand() % Hen::hens.size();
            int r5 = rand() % Hen::hens.size();
            int r6 = rand() % Hen::hens.size();
            int r7 = rand() % Hen::hens.size();
            int r8 = rand() % Hen::hens.size();
            int r9 = rand() % Hen::hens.size();
            int r10 = rand() % Hen::hens.size();
            int r11 = rand() % Hen::hens.size();
            int r12 = rand() % Hen::hens.size();
            int r13 = rand() % Hen::hens.size();

            // random numbers should not be the same
            if(r1 != r2 && r1 != r3 && r1 != r4 && r1 != r5 && r1 != r6 && r1 != r7
                    && r1 != r8 && r1 != r9 && r1 != r10 && r1 != r11 && r1 != r12 && r1 != r13
                    && r2 != r3 && r2 != r4 && r2 != r5 && r2 != r6
                    && r2 != r7 && r2 != r8 && r2 != r9 && r2 != r10 && r2 != r11
                    && r2 != r12 && r2 != r13 && r3 != r4 && r3 != r5 && r3 != r6 && r3 != r7
                    && r3 != r8 && r3 != r9 && r3 != r10 && r3 != r11 && r3 != r12 && r3 != r13
                    && r4 != r5 && r4 != r6 && r4 != r7 && r4 != r8 && r4 != r9 && r4 != r10
                    && r4 != r11 && r4 != r12 && r4 != r13 && r5 != r6 && r5 != r7
                    && r5 != r8 && r5 != r9 && r5 != r10 && r5 != r11 && r5 != r12 && r5 != r13
                    && r6 != r7 && r6 != r8 && r6 != r9 && r6 != r10 && r6 != r11 && r6 != r12
                    && r6 != r13 && r7 != r8 && r7 != r9 && r7 != r10 && r7 != r11 && r7 != r12
                    && r7 != r13 && r8 != r9 && r8 != r10 && r8 != r11 && r8 != r12
                    && r8 != r13 && r9 != r10 && r9 != r11 && r9 != r12
                    && r9 != r13 && r10 != r11 && r10 != r12 && r10 != r13 && r11 != r12
                    && r11 != r13 && r12 != r13){
                vec.append(r1);
                vec.append(r2);
                vec.append(r3);
                vec.append(r4);
                vec.append(r5);
                vec.append(r6);
                vec.append(r7);
                vec.append(r8);
                vec.append(r9);
                vec.append(r10);
                vec.append(r11);
                vec.append(r12);
                vec.append(r13);
                b = true;
            }
        }
        //droping
        for(int i = 0; i <= 12; i++){
            Hen::hens[vec[i]]->drop_Egg();
        }
    }

    // level up ...
    if(enemy_number == 0 && ship->get_lives() > 0){
    ship->setPos(880,800);
    QCursor::setPos(880,800);
    show_levelUpBoard();
    scene->addItem(levelUp_board);
    if((time_count - 4) == levelUp_time){

    if(level == 6){                      // to check victory
        Start_menu *sm = new Start_menu(1);
        sm->show();
        game->close();
    }
    else{
    time_count= 0;
    ++level;
    int n = ship->get_lives(); // keep the lives for the remaining levels
    SceneSet();                // lives = 3
    ship->set_lives(n);        // but the former lives will be set on it

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
        QPixmap image(":/images/lose.png");
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
        QPixmap image(":/images/win.png");
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

void Game::show_meatBoard()
{
    meat_board = new QGraphicsTextItem;
    meat_board->setPlainText(QString::number(meat_number));
    meat_board->setPos(260,930);
    meat_board->setDefaultTextColor(Qt::red);
    meat_board->setFont(*meat_font);

}

// updating all of the boards ...
void Game::check_status(){
    //setplaintext() is for when you want to update a text
    lives_board->setPlainText(QString::number(ship->get_lives()));

    score_board->setPlainText(QString::number(score));

    meat_board->setPlainText(QString::number(meat_number));
}



void Game::addEnemy(){
    //clearing vectors before leveling up
    Egg::eggs.clear();
    Hen::hens.clear();

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
                auto chicken = new Chicken(240 + j*170 , -i*120 , i , chicken_time);
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
                    auto hen = new Hen(300 + j*170 , -i*120 , i , chicken_time, EnemyDrop_time);
                    Hen::hens.append(hen);// adding the hen to our hen list
                    scene->addItem(hen);
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
                    auto hen = new Hen(180 + j*170 , -i*120 , i , chicken_time, EnemyDrop_time);
                    Hen::hens.append(hen);// adding the hen to our hen list
                    scene->addItem(hen);
                }
            }
        }
    }

    if(level == 5){
        enemy_number = 18;
        for(int i = 0 ; i <= 2 ; i++){ // rows
            for(int j = 0 ; j <= 5 ; j++){
                if(j%2 == 0){
                auto hen = new Hen(500 + j*170 , -i*120 , i , chicken_time, EnemyDrop_time);
                Hen::hens.append(hen);// adding the hen to our hen list
                scene->addItem(hen);
                }
                else{
                    auto superhen = new SuperHen(500 + j*170 , -i*120 , i , chicken_time, EnemyDrop_time);
                    Hen::hens.append(superhen);
                    scene->addItem(superhen);
                }
            }
        }
    }

    if(level == 6){
        enemy_number = 27;
        for(int i = 0 ; i <= 2 ; i++){ // rows
            for(int j = 0 ; j <= 8 ; j++){
                auto superhen = new SuperHen(275 + j*170 , -i*130 , i , chicken_time, EnemyDrop_time);
                Hen::hens.append(superhen);
                scene->addItem(superhen);
            }
        }
    }

}
