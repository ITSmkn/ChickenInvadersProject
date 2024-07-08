#include "Prize.h"

Prize::Prize(QTimer* t) : FallingItems(t){
    setPixmap(QPixmap(":/images/src/images/prize.png"));
}

void Prize::MoveDown(){

}
