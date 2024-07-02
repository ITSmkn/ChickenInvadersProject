#include "Start_Menu.h"


#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    // bringing the pic to work
    QPixmap backgroundImage("background.png");

    // adding pic to the scene
    QGraphicsItem *backgroundImageItem = scene.addPixmap(backgroundImage);


    // creating the view
    QGraphicsView view(&scene);
    view.setFixedSize(1512, 850);
    view.show();

    return a.exec();
}
