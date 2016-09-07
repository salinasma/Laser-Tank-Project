// Lab9.c
// Runs on LM4F120 or TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 4/12/2016 

// Analog Input connected to PE2=ADC1
// displays on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats
// UART1 on PC4-5
// * Start with where you left off in Lab8. 
// * Get Lab8 code working in this project.
// * Understand what parts of your main have to move into the UART1_Handler ISR
// * Rewrite the SysTickHandler
// * Implement the s/w FiFo on the receiver end 
//    (we suggest implementing and testing this first)

#include <stdint.h>

#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "FiFo.h"
#include "TankDriver.h"
#include "Turret.h"
#include "LaserShoot.h"
#include "Targets.h"

//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on Nokia
// main3 adds your convert function, position data is no Nokia

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void mainInit(void);
int8_t invertData(int8_t data);

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
uint32_t Data;      // 12-bit ADC
uint32_t Position;  // 32-bit fixed-point 0.001 cm
int32_t TxCounter = 0;
int8_t mailbox = 0;

uint32_t convertADC(uint32_t raw){
		int converted = ((int) raw );
	
	if(((converted - 2050) > 0) && ((converted - 2150) < 0))
		return 0;	
	return (((converted - 2048) * 100)/2048);}

	
//	int32_t convertX(uint32_t rawX){ //the absolute value of the number will give us the strength
//																	// the sign will tell us if it is going forward or backwards
//	int converted = ((int) rawX );
//	if(((converted - 2050) > 0) && ((converted - 2150) < 0))
//		return 0;
//	return (((converted - 2048) * 100)/2048);
//}
// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_RCGCGPIO_R & 0x20) == 0){};//port a = 1 b =2 c = 4 d = 8 e = 10 f = 20
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_DEN_R |= 0x0E;

}

int main(void){  
	
	TExaS_Init();       // Bus clock is 80 MHz 
	tankDrInit();
	ADC_Init();    // initialize to sample ADC1
	PortF_Init();
	FiFo_Init();
	UART_Init();
	//Turret_Init();
	//Shoot_Init();
  TargetsInit();
	DisableInterrupts();
	
	
//	GPIO_PORTA_DIR_R &= 0x80;
//	GPIO_PORTA_DEN_R |= 0x80;
	while(1){
		
		TargetHit();
//		UART_OutChar(0xFF);
//		uint8_t xJoystick = UART_InChar();
//		//xJoystick = invertData(xJoystick);
//	//	xJoystick += 0;
//		int8_t yJoystick = UART_InChar();
//		int8_t fAndT = UART_InChar();
//LASER CODE		
	//fire();
//		for(int del = 0; del < 1000000; del++){}
//  ceaseFire();
//		for(int del = 0; del < 1000000; del++){}
//		
//		if(TargetHit())
//			GPIO_PORTF_DATA_R ^= 0x08;
		


		
//int i;

		uint8_t jInputY =0;
		int8_t jInputX =0;
		uint8_t turret = 
		0;
		
		jInputX = UART_InChar();
		//jInputY = UART_InChar();
		//turret = UART_InChar();
////		jInputY = convertADC();
		//jInputX = convertADC();
	move(jInputX, jInputY);
	if(jInputX  == 0)//still
		move( 0, 0 );
	if(jInputX  == 1)//fwd
		move( 0, 100 );
	if(jInputX  == 2)//bwd
		move( 0, -100 );
	if(jInputX  == 3)
		move( 100, 0 );
	if(jInputX  == 4)
		move( -100, 0 );
	
		//move( 100, 100 );
		Turret_Move(turret);
		//Turret_Move(60);
		if(TargetHit()){
			GPIO_PORTF_DATA_R |=0x08;
			GPIO_PORTA_DATA_R |=0x80;
		}
		else{
			GPIO_PORTF_DATA_R &=~(0x08);
			GPIO_PORTA_DATA_R &=~(0x80);}
		fire();

//		
//		int deg = 115; //INSERT READ FROM UART HERE
//			Turret_Move(deg/2);
	}
}


//3.6Kohms

int8_t invertData(int8_t data){
int8_t inverted = ((data & 0x80)>> 7)+((data & 0x40)>> 5) + ((data & 0x20)>> 3)+ 
									((data & 0x10)>> 1)+ ((data & 0x08)<< 1)+ ((data & 0x04)<< 3)+ 
									((data & 0x02)<< 5)+ ((data & 0x01)<< 7);
return inverted;
}

void HardFault_Handler(){
	//GPIO_PORTF_DATA_R |=0X08;
}

void UART1_Handler(){
	UART1_ICR_R = 0x10;


	if((UART1_RIS_R & 0x40) == 0){

		if(FiFo_Put(UART_InChar())  == 0 )//1
			GPIO_PORTF_DATA_R ^= 0X08;
		if(FiFo_Put(UART_InChar())  == 0 )//2
			GPIO_PORTF_DATA_R ^= 0X08;
		if(FiFo_Put(UART_InChar())  == 0 )//3
			GPIO_PORTF_DATA_R ^= 0X08;
////		if(FiFo_Put(UART_InChar())  == 0 )//4
////			TxCounter++;
////		if(FiFo_Put(UART_InChar())  == 0 )//5
////			TxCounter++;
////		if(FiFo_Put(UART_InChar())  == 0 )//6
////			TxCounter++;
////		if(FiFo_Put(UART_InChar())  == 0 )//7
////			TxCounter++;
////		if(FiFo_Put(UART_InChar())  == 0 )//8
////			TxCounter++;

	}
	

}


void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 2000;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R |= 7;
}

void SysTick_Handler (void){

}


