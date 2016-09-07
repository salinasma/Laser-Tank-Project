#include "tm4c123gh6pm.h"


void Turret_Init(void){
        SYSCTL_RCGCGPIO_R |= 0x01;
        int delay; delay++; delay++;

        GPIO_PORTA_DIR_R |= 0x04;
        GPIO_PORTA_AMSEL_R &= ~0x04;
        GPIO_PORTA_DEN_R |= 0x04;


}



        //upper = (deg*124)+12000

void Turret_Move(int deg){

                GPIO_PORTA_DATA_R &= ~0x04;
                for(int i = 0; i < 200000; i++){}
                GPIO_PORTA_DATA_R |= 0x04;
                for(int i = 0; i < ((deg*124)+12000); i++){}

}

