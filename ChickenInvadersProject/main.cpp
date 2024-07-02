#include "Start_Menu.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto st = new Start_menu();
    st->show();

    return a.exec();
}
