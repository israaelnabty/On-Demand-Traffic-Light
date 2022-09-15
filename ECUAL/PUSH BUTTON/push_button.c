/*
 * push_button.c
 *
 * Created: 8/31/2022 4:59:54 PM
 *  Author: Israa
 */ 

/* Included Files */
#include "push_button.h"

/* Functions Prototypes */
/* Push Button Pins Initialization */
EN_PBUTT_error_t PBUTTON_init(uint8_t portBUTT, uint8_t pinNum)
{
	/* Define the pin as input */
	EN_DIO_error_t errorDIO = DIO_init(portBUTT, pinNum, INPUT_PIN);;
	if (errorDIO == DIO_INVALID_PORT)
	{
		return PBUTT_INVALID_PORT;
	}
	else if(errorDIO == DIO_INVALID_PIN)
	{
		return PBUTT_INVALID_PIN;
	}
	/* Return OK if there is no error */
	return PBUTT_OK;
}

/* Read Push Button */
EN_PBUTT_error_t PBUTTON_read(uint8_t portBUTT, uint8_t pinNum, uint8_t* valueRead)
{
	/* Read the value on the pin */
	EN_DIO_error_t errorDIO = DIO_read(portBUTT, pinNum, valueRead);
	
	if (errorDIO == DIO_INVALID_PORT)
	{
		return PBUTT_INVALID_PORT;
	}
	else if(errorDIO == DIO_INVALID_PIN)
	{
		return PBUTT_INVALID_PIN;
	}
	/* Return OK if there is no error */
	return PBUTT_OK;
}