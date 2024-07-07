#ifndef SUPERHEN_H
#define SUPERHEN_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QTimer>
#include "Enemy.h"

class SuperHen : public Enemy{
    Q_OBJECT
public:
    SuperHen(int n1, int n2, int r, QTimer* t);

    void decrease_FoeLives() override;

public slots:
    //overriding wiggle for chicken class
    void wiggle() override;
};

#endif // SUPERHEN_H
