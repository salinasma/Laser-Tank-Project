#include <stdint.h>
#include "tm4c123gh6pm.h"

void UART_Init(void){

	SYSCTL_RCGCUART_R |= 0x00000002;  // activate UART1
	SYSCTL_RCGCGPIO_R |= 0x00000004;  // activate port C

	UART1_CTL_R &= ~0x00000001;    // disable UART                                          //WE NEED TO CHANGE FROM THE LEGACY REGISTER TO THE NEW REGISTERS IF WE WANT THIS TO WORK
	UART1_IBRD_R = 260;
	UART1_FBRD_R = 27;
	UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
	UART1_IM_R |= 0x10; // Arm RXRIS
	UART1_IFLS_R |= 0x20;

	NVIC_PRI1_R   |= 0x00E00000;// bits 21-23
	NVIC_EN0_R              |= 0x40;// enable interrupt 6 in NVIC

	UART1_CTL_R |= 0x00000001;     // enable UART
	GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
	GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
	GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
	GPIO_PORTC_AMSEL_R &= ~0x30;   // disable analog on PC5-4
	}



unsigned char UART_InChar(void){
  while((UART1_FR_R&0x0010) != 0);      // wait until RXFE is 0
  return((unsigned char)(UART1_DR_R&0xFF));
}

/////////////////////////////////////////////////////////////////////


void UART_OutChar(unsigned char data){
  while((UART1_FR_R&0x0020) != 0);      // wait until TXFF is 0
  UART1_DR_R = data;
}
