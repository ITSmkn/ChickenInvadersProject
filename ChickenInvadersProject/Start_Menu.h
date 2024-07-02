#ifndef START_MENU_H
#define START_MENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class Start_menu : public QMainWindow {
    Q_OBJECT


public:

    int button_width;
    int button_height;

    QPushButton  *Exit ;
    QPushButton  *Start;

    Start_menu();

    ~Start_menu();

};
#endif // START_MENU_H
