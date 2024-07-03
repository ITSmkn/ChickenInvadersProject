#include "Start_Menu.h"
#include <game.h>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>

Game *game;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto st = new Start_menu();
    st->show();

    return a.exec();
}
