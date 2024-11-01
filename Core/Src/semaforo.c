#include "semaforo.h"

static Estado estado_actual = ESTADO_INICIAL;
static uint32_t tiempo_anterior = 0;
static const uint32_t intervalo = 200;
static int interaccion = 0;
static int interaccion2 = 0;

void Semaforo_Init(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void Semaforo_Update(void) {
    switch (estado_actual) {
        case ESTADO_INICIAL:
        	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
        	    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET) {
                estado_actual = ESTADO_INTERACCION_1;
                interaccion = 0;
                tiempo_anterior = HAL_GetTick();
            }
            break;

        case ESTADO_INTERACCION_1:
            if (interaccion < 5) {
                if (HAL_GetTick() - tiempo_anterior >= intervalo) {
                    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                    tiempo_anterior = HAL_GetTick();
                    interaccion++;
                }
            } else {
                estado_actual = ESTADO_INTERACCION_2;
                interaccion2 = 0;
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                tiempo_anterior = HAL_GetTick();
            }
            break;

        case ESTADO_INTERACCION_2:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            if (interaccion2 < 15) {
                if (HAL_GetTick() - tiempo_anterior >= intervalo) {
                    tiempo_anterior = HAL_GetTick();
                    interaccion2++;
                }
            } else {
                estado_actual = ESTADO_INTERACCION_3;
                interaccion2 = 0;
                tiempo_anterior = HAL_GetTick();
            }
            break;

        case ESTADO_INTERACCION_3:
            if (interaccion2 < 5) {
                if (HAL_GetTick() - tiempo_anterior >= intervalo) {
                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
                    tiempo_anterior = HAL_GetTick();
                    interaccion2++;
                }
            } else {
                estado_actual = ESTADO_FINAL;
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            }
            break;

        case ESTADO_FINAL:
            // Aquí puedes reiniciar el FSM o hacer algo más
            estado_actual = ESTADO_INICIAL; // Reiniciar o finalizar
            Semaforo_Init(); // Reiniciar el estado
            break;

        default:
            estado_actual = ESTADO_INICIAL; // Reset en caso de error
            break;
    }
}
