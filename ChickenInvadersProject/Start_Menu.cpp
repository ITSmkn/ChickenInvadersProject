#include "Start_Menu.h"


Start_menu::Start_menu(){


    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    button_width = 700;
    button_height = 80;

    Start = new QPushButton( "Start Game" , this);
    Exit = new QPushButton("Exit" , this);


    Start->setGeometry(x() , y()*2 , button_width , button_height);
    this->layout()->addWidget(Start);
    Start->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    this->layout()->addWidget(Exit);
    Exit->setGeometry(x()+175 , y()*2+120 , button_width/2  ,button_height);
    Exit->setIconSize(QSize(35 , 35));


    showMaximized();

}

Start_menu::~Start_menu()
{

    delete Start;
    delete Exit;

}

