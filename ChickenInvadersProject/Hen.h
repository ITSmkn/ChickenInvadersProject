#ifndef HEN_H
#define HEN_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QTimer>

#include "Enemy.h"
#include "Egg.h"


class Hen : public Enemy{
    Q_OBJECT
public:
    //for droping eggs and meats
    QTimer* drop_time;

    Hen(int n1, int n2, int r, QTimer *t, QTimer *t2);

    void drop_Egg();

    void decrease_FoeLives() override;

    static QVector<Hen*> hens;//for save all of the hens to choose randomly for droping eggs

public slots:
    //overriding wiggle for hen class
    virtual void wiggle() override;
};

#endif // HEN_H
