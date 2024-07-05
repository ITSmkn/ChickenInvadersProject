#ifndef ROCKET_H
#define ROCKET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>


class Rocket :public QObject ,public QGraphicsPixmapItem{
private:
    Q_OBJECT

public:

    // timer for the rocket object to move ...
    QTimer * time;

    Rocket(QTimer* t); //constructor gets a QTimer pointer ...

public slots:

    //function for rocket's movement (will be connected to the time) ...
    void move();
};



#endif // ROCKET_H
