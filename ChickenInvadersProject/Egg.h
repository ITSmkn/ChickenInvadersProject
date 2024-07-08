#ifndef EGG_H
#define EGG_H

#include "FallingItems.h"

class Egg : public FallingItems{
    Q_OBJECT

public:
    bool reached;
    static QVector<Egg*> eggs;//for saving all of the eggs in a particular level

    Egg(QTimer*);

public slots:
    void MoveDown() override;
};

#endif // EGG_H
