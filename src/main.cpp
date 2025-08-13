#include "Start_Menu.h"
#include "game.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

Game *game;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    auto st = new Start_menu(1);
    st->show();


    return a.exec();
}
