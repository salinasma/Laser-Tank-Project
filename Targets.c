#include "tm4c123gh6pm.h"

void TargetsInit(){
SYSCTL_RCGCGPIO_R |= 0x02;
int delay = 0; delay++; delay++;
GPIO_PORTB_DIR_R &= ~(0x0F);  
GPIO_PORTB_DEN_R |= 0x0F; // input is zero
}
char TargetHit(){
	if((GPIO_PORTB_DATA_R & 0x0F) > 0){
		GPIO_PORTF_DATA_R |=0x08;
		return 1;
	}
		
	//return 1;
	else {
		GPIO_PORTF_DATA_R &=~(0x08);
	}
	return 0;
	//		if((GPIO_PORTA_DATA_R & 0x80) == 0x80)
//			GPIO_PORTF_DATA_R |=0x08;
//		else
//			GPIO_PORTF_DATA_R &=~(0x08);
}
