#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "stm32f1xx_hal.h"

typedef enum {
    ESTADO_INICIAL,
    ESTADO_INTERACCION_1,
    ESTADO_INTERACCION_2,
    ESTADO_INTERACCION_3,
    ESTADO_FINAL
} Estado;

void Semaforo_Init(void);
void Semaforo_Update(void);

#endif // SEMAFORO_H
