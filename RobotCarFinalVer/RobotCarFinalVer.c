/*
 * RobotCarFinalVer.c
 *
 * Created: 18/1/2024 3:39:09 PM
 *  Author: OoiZhiYi & PuaKianYang
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

// Global Variable
unsigned char radiationCount = 0;
unsigned char location = 0;
unsigned char affectedGrid[6] = {};
unsigned char BlackLineCount = 0;
unsigned char ProgramCondition = 0;
unsigned char DisplayCondition = 0;
unsigned char Scan = 1;
unsigned char i = 0;
unsigned char k = 0;

void MotorBackward();
void MotorForward();
void MotorLeft();
void MotorReset();
void radiationCountDisplay();
void affectedGridDisplay();

//PB4 = Start & Stop button
//PB5 = Display button
//PB1 = Black line sensor
//PB0 = Radiation Sensor

///////////////////////////////////////////////////////////////////////////////////////
//Main program start

int main(void)
{
	DDRA = 0xFF; //PortA Output
	DDRB = 0x00; //PortB Input
	DDRC = 0xFF; //PortC Output
	DDRD = 0xFF; //PortD Output
	
    while(1)
    {	
		if(PINB &= 0b00010000){
			ProgramCondition = 1;		// Enable the main program
			_delay_ms(2000);			
		}
		
		if(BlackLineCount>=9){
			ProgramCondition = 0;		// Disable the main program
			if(k==0){
				MotorForward();			// Moving out from the 6th box
				_delay_ms(6000);
				MotorReset();			// Stop moving
				k++;
			}
			if (PINB &= 0b00100000){
				DisplayCondition = 1;	// Enable the display program
			}
		}
		
		if(ProgramCondition==1){
			MotorForward();				// The robot moving forward
			_delay_ms(450);
			MotorReset();				// The robot stop moving
			_delay_ms(3500);
			if(PINB &= 0b00010000){		// Stop button 
				MotorReset();			
				while(1){
					if(PINB &= 0b00100000){			// Display button
						radiationCountDisplay();	// Show the total radiation area counted
						
						if(radiationCount==0){
							PORTA = 0x3F;			// Show 0 on the seven segment display
						}else{
							affectedGridDisplay();	// Show the location of boxes that affected by radiation
						}
					}
				}
			}
				if ((PINB &= 0b00000010)){			// If blackLine sensor detected blackLine
					BlackLineCount++;				// Black line count + 1
					Scan=1;							// Enable radiation scanning
					PORTD=0b10000000;				// Red LED on
					_delay_ms(1000);
					PORTD=0x00;						// Red LED off

					if(BlackLineCount==1 || BlackLineCount==2 || BlackLineCount== 3 || BlackLineCount==5 || BlackLineCount==7 || BlackLineCount==8){
						location++;
						if(radiationCount<=5){
							for(int a=0; a<7; a++){								// Move forward and scan 7 times
								MotorForward();
								_delay_ms(450);
								MotorReset();
								_delay_ms(3500);
								if(Scan==1){
									if (BlackLineCount!=4 || BlackLineCount!=6){
										if (PINB &= 0b00000001){				// Scan the radiation area
											PORTA=0b10000000;					// Blue LED on
											_delay_ms(1000);
											PORTA=0x00;							// Blue LED off
											radiationCount++;					// Radiation count + 1
											affectedGrid[i]=location;			// Store the location into array
											i++;
											Scan=0;								// Disable radiation area detection
										}
									}
								}
							}
						}
					}
					if (BlackLineCount==4){				//If Black line detected is 4
						for(int b=0; b<5; b++){
							MotorBackward();			// Reverse
							_delay_ms(1300);
							MotorReset();				// Motor stop
							_delay_ms(3000);
						}
						MotorReset();
						_delay_ms(2000);
						MotorLeft();
						_delay_ms(6500);				// Turn left
						MotorReset();
						_delay_ms(2000);
						Scan=0;							// Disable radiation area detection
					}else if(BlackLineCount==6){
						for(int b=0; b<5; b++){
							MotorBackward();			// Reverse
							_delay_ms(1300);
							MotorReset();				// Motor stop
							_delay_ms(3000);
						}
						MotorReset();
						_delay_ms(2000);
						MotorLeft();
						_delay_ms(6800);				// Turn left
						MotorReset();
						_delay_ms(2000);
						Scan=0;							// Disable radiation area detection
					}
					
					
				}
		}
		if (DisplayCondition==1){
			while(1){	
				radiationCountDisplay();				// Display total radiation area counted
				if(radiationCount==0){
					PORTA = 0x3F;						// Show 0 on the seven segment display
				}else{
					affectedGridDisplay();				// Display the location of affected grid
				}
			}	
		}	
	}		
}

void radiationCountDisplay()
{
	
	switch(radiationCount)
	{
		case 0:
		PORTD = 0x3F;
		break;
		
		case 1:
		PORTD = 0x06;
		break;
		
		case 2:
		PORTD = 0x5B;
		break;
		
		case 3:
		PORTD = 0x4F;
		break;
		
		case 4:
		PORTD = 0x66;
		break;
		
		case 5:
		PORTD = 0x6D;
		break;
		
		case 6:
		PORTD = 0x7D;
		break;
		
		default:
		PORTD = 0xFF;
	}
}

void MotorForward(){
	PORTC = 0b10000010; //Move Forward
}

void MotorBackward(){
	PORTC = 0b01000001; //Move Backward
}

void MotorLeft(){
	PORTC = 0b01000010; //Move Forward
}

void MotorReset(){
	PORTC = 0b00000000; //Reset Motor
}

void affectedGridDisplay()
{
	for (int j = 0; j < radiationCount; j++)
	{
		uint8_t grid = affectedGrid[j];
		
		switch(grid)
		{
			case 0:
			PORTA = 0x3F;
			break;
			
			case 1:
			PORTA = 0x06;
			break;
			
			case 2:
			PORTA = 0x5B;
			break;
			
			case 3:
			PORTA = 0x4F;
			break;
			
			case 4:
			PORTA = 0x66;
			break;
			
			case 5:
			PORTA = 0x6D;
			break;
			
			case 6:
			PORTA = 0x7D;
			break;
			
			default:
			PORTA = 0xFF;
		}
		_delay_ms(8000);
	}
}