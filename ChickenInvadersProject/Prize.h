#ifndef PRIZE_H
#define PRIZE_H

#include "FallingItems.h"

class Prize : public FallingItems{
    Q_OBJECT
public:
    Prize(QTimer*);

public slots:
    void MoveDown() override;
};

#endif // PRIZE_H
