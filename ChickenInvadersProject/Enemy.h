#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>


class Enemy : public QObject , public QGraphicsPixmapItem{

    Q_OBJECT
protected:
    int X, Y;
    int rows;
    int FoeLives ;
    QTimer* time ;
    // temp is an int variable dedicated to our wiggle virtual method ...
    int temp;

public:

    Enemy(int n1, int n2 , int r,QTimer* t);

    int get_FoeLives();

    //a function to handle enemies lives
    virtual void decrease_FoeLives() = 0;//(abstract)

public slots:

    // the function for enemies wiggling ... (abstract)
    virtual void wiggle() = 0;

    void MoveDown();



};

#endif // ENEMY_H
