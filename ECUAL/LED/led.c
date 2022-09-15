/*
 * led.c
 *
 * Created: 8/31/2022 5:00:47 PM
 *  Author: Israa
 */ 

/* Included Files */
#include "led.h"

/* Define Global Variables */
uint8_t stopBlinkLED = 0;
uint8_t stopMultiBlinkLED = 0;

/* Functions Definitions */
/* LED Pins Initialization */
EN_LED_error_t LED_init(uint8_t portLED, uint8_t pinNum)
{
	/* Define the pin as output */
	EN_DIO_error_t errorDIO = DIO_init(portLED, pinNum, OUTPUT_PIN);
	if (errorDIO == DIO_INVALID_PORT)
	{
		return LED_INVALID_PORT;
	} 
	else if(errorDIO == DIO_INVALID_PIN)
	{
		return LED_INVALID_PIN;
	}
	/* Return OK if there is no error */
	return LED_OK;
}

/* LED On */
EN_LED_error_t LED_on(uint8_t portLED, uint8_t pinNum)
{	
	/* Write 1 on the pin */
	EN_DIO_error_t errorDIO = DIO_write(portLED, pinNum, HIGH);
	if (errorDIO == DIO_INVALID_PORT)
	{
		return LED_INVALID_PORT;
	}
	else if(errorDIO == DIO_INVALID_PIN)
	{
		return LED_INVALID_PIN;
	}
	/* Return OK if there is no error */
	return LED_OK;
}

/* LED Off */
EN_LED_error_t LED_off(uint8_t portLED, uint8_t pinNum)
{
	/* Write 0 on the pin */
	EN_DIO_error_t errorDIO = DIO_write(portLED, pinNum, LOW);
	if (errorDIO == DIO_INVALID_PORT)
	{
		return LED_INVALID_PORT;
	}
	else if(errorDIO == DIO_INVALID_PIN)
	{
		return LED_INVALID_PIN;
	}
	/* Return OK if there is no error */
	return LED_OK;
}

/* LED Toggle */
EN_LED_error_t LED_toggle(uint8_t portLED, uint8_t pinNum)
{
	/* Toggle the pin output */
	EN_DIO_error_t errorDIO = DIO_toggle(portLED, pinNum);
	if (errorDIO == DIO_INVALID_PORT)
	{
		return LED_INVALID_PORT;
	}
	else if(errorDIO == DIO_INVALID_PIN)
	{
		return LED_INVALID_PIN;
	}
	/* Return OK if there is no error */
	return LED_OK;
}

/* LED Blink */
EN_LED_error_t LED_blink(uint8_t portLED, uint8_t pinNum, float timeBlink_ms)
{
	float toggleTime_ms = 500; /* 500ms*/
	uint8_t blinkNum = (uint8_t)(timeBlink_ms/(2*toggleTime_ms) + 0.5); /* Rounding to the nearest integer */
	EN_LED_error_t errorLED;
	/* Start with LED off and to check errors */
	errorLED = LED_off(portLED, pinNum);
	if (errorLED == LED_INVALID_PORT)
	{
		return LED_INVALID_PORT;
	}
	else if (errorLED == LED_INVALID_PIN)
	{
		return LED_INVALID_PIN;
	}
	
	/* Start Blinking */
	for (uint8_t blinkCount = 0; (blinkCount < blinkNum)&&(stopBlinkLED == 0); blinkCount++)
	{
		/* LED on */
		errorLED = LED_on(portLED, pinNum);
		/* Delay by toggleTime */
		TIMER0_delay_ms(toggleTime_ms);
		/* Busy Wait for the timer0 end */
		while(TIMER0_isDelayFinished() != 1);
		
		/* LED off */
		errorLED = LED_off(portLED, pinNum);
		/* Delay by toggleTime */
		TIMER0_delay_ms(toggleTime_ms);
		/* Busy Wait for the timer0 end */
		while(TIMER0_isDelayFinished() != 1);
	}
	/* Reset Stop Blink Variable */
	stopBlinkLED = 0;
	/* Return OK if there is no error */
	return LED_OK;
}

/* Multiple LEDs Blink */
EN_LED_error_t LED_blinkMultiple(uint8_t* portLED, uint8_t* pinNum, uint8_t numOfLEDs, float timeBlink_ms)
{
	float toggleTime_ms = 500; /* 5ms*/
	uint8_t blinkNum = (uint8_t)(timeBlink_ms/(2*toggleTime_ms) + 0.5); /* Rounding to the nearest integer */
	uint8_t blinkCount = 0; 
	uint8_t countLED = 0;
	EN_LED_error_t errorLED;
	/* Start with LEDs off and to check errors */
	for (countLED = 0; countLED < numOfLEDs; countLED++)
	{
		errorLED = LED_off(portLED[countLED], pinNum[countLED]);
		if (errorLED == LED_INVALID_PORT)
		{
			return LED_INVALID_PORT;
		}
		else if (errorLED == LED_INVALID_PIN)
		{
			return LED_INVALID_PIN;
		}
	}
	/* Start Blinking */
	for (blinkCount = 0; (blinkCount < blinkNum)&&(stopMultiBlinkLED == 0); blinkCount++)
	{
		/* LEDs on */
		for (countLED = 0; (countLED < numOfLEDs)&&(stopMultiBlinkLED == 0); countLED++)
		{
			errorLED = LED_on(portLED[countLED], pinNum[countLED]);	
		}		
		/* Delay by toggleTime */
		TIMER0_delay_ms(toggleTime_ms);
		/* Busy Wait for the timer0 end */
		while(TIMER0_isDelayFinished() != 1);
		
		/* LEDs off */
		for (countLED = 0; (countLED < numOfLEDs)&&(stopMultiBlinkLED == 0); countLED++)
		{
			errorLED = LED_off(portLED[countLED], pinNum[countLED]);
		}
		/* Delay by toggleTime */
		TIMER0_delay_ms(toggleTime_ms);
		/* Busy Wait for the timer0 end */
		while(TIMER0_isDelayFinished() != 1);
	}
	/* Reset Stop Blink Variable */
	stopMultiBlinkLED = 0;
	/* Return OK if there is no error */
	return LED_OK;
}

