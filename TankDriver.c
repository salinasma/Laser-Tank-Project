#include <stdint.h>
#include "tm4c123gh6pm.h"


#define FWD  			0x60//0x18
#define FWDLeght	0x20//0x08
#define FWDRight	0x40 //0x10


#define BKW  			0x18//0x60
#define BKWLeght	0x08//0x20
#define BKWRight	0x10//0x40 
 	

#define RIGHT 		0x48
#define LEFT  		0x30 
#define STILL 		0x00

void tankDrInit(){
	SYSCTL_RCGCGPIO_R |= 0x01;
	int delay; delay++; delay++; 

	GPIO_PORTA_DIR_R |= 0x0F8;
	GPIO_PORTA_DEN_R |= 0x0F8;
	GPIO_PORTA_DIR_R |= 0x04;
	GPIO_PORTA_AMSEL_R &= ~0x04;
	GPIO_PORTA_DEN_R |= 0x04;
	
	
	 
   

   
//	GPIO_PORTA_DIR_R &= ~(0x0010);
//	GPIO_PORTA_DEN_R |= 0x010;
}



//                GPIO_PORTA_DATA_R &= ~0x04;
//                for(int i = 0; i < 200000; i++){}
//                GPIO_PORTA_DATA_R |= 0x04;
//                for(int i = 0; i < ((deg*124)+12000); i++){}





void move(int xData, int yData){//, uint8_t turret) { //max for high pulse is 4000
	//int j;
	//int lowDefault = 200;
	//int highPulse = 0;
	//int xRight = 0;
	//int xLeght = 0;
	//int leghtTrack = 0;
	//int rightTrack = 0;
	int dir = 0;
	
	
//	
		if(yData >= 0){
//		leghtTrack = FWDLeght;
//		rightTrack = FWDRight;
//		highPulse = (40)*yData; // high pulse calulations
			dir = FWD;
		}	
	else if (yData < 0){
//		leghtTrack = BKWLeght;
//		rightTrack = BKWRight;
//		highPulse = (-40)*yData; // high pulse calulations
		dir = BKW;
	}
//	if(xData >= 0){
//		xLeght = highPulse;
//		xRight = (xLeght*75)/100 +((xLeght * xData )/400);//
//	}
//	else if (xData <0){
//		xRight = highPulse;
//		xLeght = (((xRight*75)/100 +(xRight * xData )/400)); 
//	}
//	
	if((xData > 0) && (yData == 0)){ // the left side
			dir = LEFT;
//		leghtTrack = LEFT;
//		rightTrack = LEFT;
//		highPulse = (40)*xData;
//		xRight = highPulse;
//		xLeght = highPulse;
	}
	if((xData < 0) && (yData == 0)){
//		leghtTrack = RIGHT;
//		rightTrack = RIGHT; 
//		highPulse = (-40)*xData;
//		xRight = highPulse;
//		xLeght = highPulse;
			dir = RIGHT;
	}

//	

//	

//	for(j = 0; j < highPulse; j++){
//		if(xLeght < 0){
//			leghtTrack = 0;
//		}
//		if (xRight < 0){
//			rightTrack = 0;
//		}
//		
//		dir = (rightTrack | leghtTrack);
//		GPIO_PORTA_DATA_R = ((GPIO_PORTA_DATA_R & (~0x078)) | dir);
//		
//		xLeght--;
//		xRight--;
//	}
//	for(j = 0; j < lowDefault; j++){
//		GPIO_PORTA_DATA_R = (GPIO_PORTA_DATA_R & (~0x078)); //clears the info
//	}
	
	if ((xData == 0) && (yData == 0)){
		dir = STILL;}
	GPIO_PORTA_DATA_R = ((GPIO_PORTA_DATA_R & (~0x078)) | dir);
	
	
	
}



