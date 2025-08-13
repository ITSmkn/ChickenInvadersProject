#ifndef MEAT_H
#define MEAT_H

#include "FallingItems.h"

class Meat : public FallingItems{
    Q_OBJECT
public:
    Meat(QTimer*);

public slots:
    void MoveDown() override;
};

#endif // MEAT_H
