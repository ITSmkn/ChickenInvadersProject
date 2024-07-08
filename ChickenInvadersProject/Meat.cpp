#include "Meat.h"

Meat::Meat(QTimer* t) : FallingItems(t){
    setPixmap(QPixmap(":/images/src/images/meat.png"));
}

void Meat::MoveDown(){

}
