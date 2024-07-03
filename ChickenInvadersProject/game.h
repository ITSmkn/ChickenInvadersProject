#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>

// this class is actually related to the main game screen

class Game : public QGraphicsView{

private:
    int Width , Height;

    QGraphicsScene * scene;

public:

     Game(int width , int height);

    ~Game();

     void SceneSet();

};

#endif // GAME_H
