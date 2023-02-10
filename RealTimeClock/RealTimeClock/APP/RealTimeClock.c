/*
 * RealTimeClock.c
 *
 * Created: 29-Jan-23 4:46:19 PM
 *  Author: Qabbani
 */ 
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TIMER/TIMER_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/SEVEN_SEGMANT/SEVEN_SEG_interface.h"

#define F_CPU 8000000UL
#include <util/delay.h>
volatile u8 seconds_counter=0;
u8 minutes_counter=0,hours_counter=0;
u8 value,first_digit,second_digit;
int main(void)
{
	KEYPAD_vInit();
	LCD_vInit();
	SEVEN_SEG_vInit(DIO_PORTB);
	
	DIO_vSetLowNibbleDirection(DIO_PORTC,DIO_PIN_OUTPUT);
	DIO_vSetPinDirection(DIO_PORTC,4,DIO_PIN_OUTPUT);
	DIO_vSetPinDirection(DIO_PORTC,5,DIO_PIN_OUTPUT);
	
	LCD_vSendString("Press 1 to");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("set clock");
	TIMER2_overflow_init_interrupt();
	
	while(1)
	{
		value=KEYPAD_u8checkPress();
		if (value!=NOT_PRESSED)
		{
			if (value=='1')
			{
				
				LCD_vClearScreen();
				LCD_vSendString("hours=--");
				LCD_vMoveCursor(1,7);
				_delay_ms(500);
				do
				{
					first_digit=KEYPAD_u8checkPress();
					
				} while (first_digit==NOT_PRESSED);
				LCD_vSendChar(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=KEYPAD_u8checkPress();
					
				} while (second_digit==NOT_PRESSED);
				LCD_vSendChar(second_digit);
				_delay_ms(300);
				hours_counter=(second_digit-48)+10*(first_digit-48);
				LCD_vClearScreen();
				
				LCD_vSendString("minutes=--");
				LCD_vMoveCursor(1,9);
				do
				{
					first_digit=KEYPAD_u8checkPress();
					
				} while (first_digit==NOT_PRESSED);
				LCD_vSendChar(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=KEYPAD_u8checkPress();
					
				} while (second_digit==NOT_PRESSED);
				LCD_vSendChar(second_digit);
				_delay_ms(300);
				minutes_counter=(second_digit-48)+10*(first_digit-48);
				LCD_vClearScreen();
				
				LCD_vSendString("seconds=--");
				LCD_vMoveCursor(1,9);
				
				do
				{
					first_digit=KEYPAD_u8checkPress();
					
				} while (first_digit==NOT_PRESSED);
				LCD_vSendChar(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=KEYPAD_u8checkPress();
					
				} while (second_digit==NOT_PRESSED);
				LCD_vSendChar(second_digit);
				_delay_ms(300);
				seconds_counter=(second_digit-48)+10*(first_digit-48);
				LCD_vClearScreen();
				LCD_vSendString("press 1 to");
				LCD_vMoveCursor(2,1);
				LCD_vSendString("set clock");
			}
			else
			{
				LCD_vClearScreen();
				LCD_vSendString("wrong choice");
				_delay_ms(600);
				LCD_vClearScreen();
				LCD_vSendString("Press 1 to");
				LCD_vMoveCursor(2,1);
				LCD_vSendString("set clock");
			}
		}
		
		DIO_vSetPinValue(DIO_PORTC,1,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,2,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,3,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,4,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,5,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,0,DIO_PIN_LOW);
		
		SEVEN_SEG_vWrite(DIO_PORTB,seconds_counter%10);
		_delay_ms(5);
		
		DIO_vSetPinValue(DIO_PORTC,0,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,2,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,3,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,4,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,5,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,1,DIO_PIN_LOW);
		
		SEVEN_SEG_vWrite(DIO_PORTB,seconds_counter/10);
		_delay_ms(5);
		
		DIO_vSetPinValue(DIO_PORTC,0,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,1,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,3,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,4,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,5,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,2,DIO_PIN_LOW);
		
		SEVEN_SEG_vWrite(DIO_PORTB,minutes_counter%10);
		_delay_ms(5);
		
		DIO_vSetPinValue(DIO_PORTC,0,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,1,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,2,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,4,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,5,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,3,DIO_PIN_LOW);
		
		SEVEN_SEG_vWrite(DIO_PORTB,minutes_counter/10);
		_delay_ms(5);
		
		DIO_vSetPinValue(DIO_PORTC,0,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,1,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,2,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,3,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,5,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,4,DIO_PIN_LOW);
		
		SEVEN_SEG_vWrite(DIO_PORTB,hours_counter%10);
		_delay_ms(5);
		
		DIO_vSetPinValue(DIO_PORTC,0,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,1,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,2,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,3,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,4,DIO_PIN_HIGH);
		DIO_vSetPinValue(DIO_PORTC,5,DIO_PIN_LOW);
		
		SEVEN_SEG_vWrite(DIO_PORTB,hours_counter/10);
		_delay_ms(5);
		
		if (seconds_counter==60)
		{
			seconds_counter=0;
			minutes_counter++;
		}
		if (minutes_counter==60)
		{
			minutes_counter=0;
			hours_counter++;
		}
		if (hours_counter==24)
		{
			hours_counter=0;
		}
	}
	
}

ISR(TIMER2_OVF_vect)
{
	seconds_counter++;
	
}

