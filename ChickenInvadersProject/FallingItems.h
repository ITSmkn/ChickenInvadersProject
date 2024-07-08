#ifndef FALLINGITEMS_H
#define FALLINGITEMS_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class FallingItems : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
protected:
    QTimer* time;

public:
    FallingItems(QTimer* t);

public slots:
    virtual void MoveDown();
};

#endif // FALLINGITEMS_H
