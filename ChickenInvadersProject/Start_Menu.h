#ifndef START_MENU_H
#define START_MENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

#include "game.h"

class Start_menu : public QMainWindow {
    Q_OBJECT

public:

    int button_width;
    int button_height;

    int n;

    QPushButton  *Exit ;
    QPushButton  *Start;

    Start_menu(int);
    ~Start_menu();


private slots:

    void F_exit();
    void Start_Game();
    void resume_game();

};
#endif // START_MENU_H
