#include "tm4c123gh6pm.h"


void Shoot_Init(void){
                SYSCTL_RCGCGPIO_R |= 0x10;
          int delay = 0; delay++; delay++;

                GPIO_PORTE_DIR_R |= 0x08;  
                GPIO_PORTE_DEN_R |= 0x08; // input is zero
}

void fire(void){
        GPIO_PORTE_DATA_R |= 0x08;

}

void ceaseFire(void){
        GPIO_PORTE_DATA_R &= ~0x08;
}
