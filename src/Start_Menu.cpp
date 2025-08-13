#include "Start_Menu.h"
#include "game.h"

extern Game *game;

Start_menu::Start_menu(int n){

    this->n = n;
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    showMaximized(); // it has to be here , otherwise the button's positions will be wrong.

    button_width = 720;
    button_height = 90;

    // exit button ...

    Exit = new QPushButton("Exit" , this);
    this->layout()->addWidget(Exit);
    Exit->setGeometry(x()+125 , y()*2+150 , button_width/2  ,button_height - 20);
    Exit->setIconSize(QSize(35 , 35));

    connect(Exit ,&QPushButton::clicked , this , &Start_menu::F_exit );   // Exit button function.

    // resume/start button ...
    if(n == 1){
           Start = new QPushButton( "Start Game" , this);
           connect(Start , &QPushButton::clicked , this , &Start_menu::Start_Game);
    }

    else{
           Start = new QPushButton( "Resume Game" , this);
           connect(Start , &QPushButton::clicked , this , &Start_menu::resume_game);
    }

    Start->setGeometry(x()-50 , y()*2 + 30 , button_width , button_height);
    this->layout()->addWidget(Start);
    Start->setFocusPolicy(Qt::FocusPolicy::NoFocus);


    // applying the changes to the buttons and so on ...
    setStyleSheet("QMainWindow{background-image:url(:/images/mainBg.png);}"
                           "QPushButton{background-color: rgba(244, 40, 11, 180);"
                           "color:rgb(255, 255, 255);"
                           "border-top-right-radius:40;border-bottom-left-radius:40;"
                           "font: 63 28pt \"Bw Stretch Medium\";"
                           "border:0.5px solid rgb(255, 255, 255);}"
                           "QPushButton:hover{background-color: rgba(29, 61, 239, 220);}"
                           "QPushButton:pressed{background-color: rgba(0, 0, 64, 200);}");
}

// should be overloaded because of the pointers that we have.
Start_menu::~Start_menu()
{
    delete Start;
    delete Exit;
}

void Start_menu::F_exit(){
    exit(0);
}

void Start_menu::Start_Game(){

    game = new Game(width() , height());
    game->show();
    this->hide();
}

void Start_menu::resume_game(){

    this->hide();
    game->resume_game();

}
