#ifndef SUPERHEN_H
#define SUPERHEN_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QTimer>
#include "Enemy.h"
#include "Hen.h"

class SuperHen : public Hen{
    Q_OBJECT
public:
    SuperHen(int n1, int n2, int r, QTimer* t, QTimer* t2);

    void decrease_FoeLives() override;

public slots:
    //overriding wiggle for superhen class
    void wiggle() override;
};

#endif // SUPERHEN_H
