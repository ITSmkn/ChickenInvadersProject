#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>


class Enemy : public QObject , public QGraphicsPixmapItem{

    Q_OBJECT

public:

    Enemy(int n1, int n2 , QTimer* t);

    int get_FoeLives();

public slots:

    // the function for enemies wiggling ... (abstract)
    virtual void wiggle();

protected:
    int x, y;
    int FoeLives ;
    QTimer* time ;
    // temp is an int variable dedicated to our wiggle virtual method ...
    int temp;

};

#endif // ENEMY_H
