#ifndef HEN_H
#define HEN_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QTimer>

#include "Enemy.h"


class Hen : public Enemy{
    Q_OBJECT
public:
    Hen(int n1, int n2, int r, QTimer *t);

    void decrease_FoeLives() override;

public slots:
    //overriding wiggle for chicken class
    void wiggle() override;
};

#endif // HEN_H
