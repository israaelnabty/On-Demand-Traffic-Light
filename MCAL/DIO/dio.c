/*
 * dio.c
 *
 * Created: 8/31/2022 4:57:25 PM
 *  Author: Israa
 */ 

/* Included Files */
#include "dio.h"

/* Functions Definitions */
/* Pins Initialization */
EN_DIO_error_t DIO_init(uint8_t portRegist, uint8_t pinNum, uint8_t pinDirection)
{
	/* Check if the pin number exceeds the maximum no. of pins in a DIO register */
	if (pinNum > (IO_MAX_NUM_PIN-1))
	{
		return DIO_INVALID_PIN;
	}
	/* Check the ports directions and names */
	if (pinDirection == INPUT_PIN)
	{
		/* Clear the bit corresponding to the given pin number */
		switch (portRegist)
		{
			case IO_PORT_A :
				CLEAR_BIT(DDRA,pinNum);
			break;
			case IO_PORT_B :
				CLEAR_BIT(DDRB,pinNum);
			break;
			case IO_PORT_C :
				CLEAR_BIT(DDRC,pinNum);
			break;
			case IO_PORT_D :
				CLEAR_BIT(DDRD,pinNum);
			break;
			default:
			    return DIO_INVALID_PORT;
		}
	}
	else if (pinDirection == OUTPUT_PIN)
	{
		/* Set the bit corresponding to the given pin number */
		switch (portRegist)
		{
			case IO_PORT_A :
				SET_BIT(DDRA,pinNum);
				break;
			case IO_PORT_B :
				SET_BIT(DDRB,pinNum);
				break;
			case IO_PORT_C :
				SET_BIT(DDRC,pinNum);
				break;
			case IO_PORT_D :
				SET_BIT(DDRD,pinNum);
				break;
			default:
				return DIO_INVALID_PORT;
		}
	}	
	else
	{
		/* Return invalid port direction */
		return DIO_INVALID_DIRECTION;
	}
	/* Return OK if there is no error */
	return DIO_OK;
}

/* Pin Write */
EN_DIO_error_t DIO_write(uint8_t portRegist, uint8_t pinNum, uint8_t valueWrite)
{
	/* Check if the pin number exceeds the maximum no. of pins in a DIO register */
	if (pinNum > (IO_MAX_NUM_PIN-1))
	{
		return DIO_INVALID_PIN;
	}
	/* Check the ports names */
	if (valueWrite == LOW)
	{
		/* Clear the bit corresponding to the given pin number */
		switch (portRegist)
		{
			case IO_PORT_A :
				CLEAR_BIT(PORTA,pinNum);
			break;
			case IO_PORT_B :
				CLEAR_BIT(PORTB,pinNum);
			break;
			case IO_PORT_C :
				CLEAR_BIT(PORTC,pinNum);
			break;
			case IO_PORT_D :
				CLEAR_BIT(PORTD,pinNum);
			break;
			default:
				return DIO_INVALID_PORT;
		}
	}
	else if (valueWrite == HIGH)
	{
		/* Set the bit corresponding to the given pin number */
		switch (portRegist)
		{
			case IO_PORT_A :
				SET_BIT(PORTA,pinNum);
			break;
			case IO_PORT_B :
				SET_BIT(PORTB,pinNum);
			break;
			case IO_PORT_C :
				SET_BIT(PORTC,pinNum);
			break;
			case IO_PORT_D :
				SET_BIT(PORTD,pinNum);
			break;
			default:
				return DIO_INVALID_PORT;
		}
	}
	else
	{
		/* Return invalid value */
		return DIO_INVALID_OUTPUT;
	}
	/* Return OK if there is no error */
	return DIO_OK;
}

/* Pin Toggle */
EN_DIO_error_t DIO_toggle(uint8_t portRegist, uint8_t pinNum)
{
	/* Check if the pin number exceeds the maximum no. of pins in a DIO register */
	if (pinNum > (IO_MAX_NUM_PIN-1))
	{
		return DIO_INVALID_PIN;
	}
	/* Check the ports names */
	switch (portRegist)
	{
		case IO_PORT_A :
			TOGGLE_BIT(PORTA,pinNum);
		break;
		case IO_PORT_B :
			TOGGLE_BIT(PORTB,pinNum);
		break;
		case IO_PORT_C :
			TOGGLE_BIT(PORTC,pinNum);
		break;
		case IO_PORT_D :
			TOGGLE_BIT(PORTD,pinNum);
		break;
		default:
			return DIO_INVALID_PORT;
	}
	/* Return OK if there is no error */
	return DIO_OK;
}

/* Pin Read */
EN_DIO_error_t DIO_read(uint8_t portRegist, uint8_t pinNum, uint8_t* valueRead)
{
	/* Check if the pin number exceeds the maximum no. of pins in a DIO register */
	if (pinNum > (IO_MAX_NUM_PIN-1))
	{
		return DIO_INVALID_PIN;
	}
	/* Check the ports names */
	switch (portRegist)
	{
		case IO_PORT_A :
			*valueRead = READ_BIT(PINA,pinNum);
			break;
		case IO_PORT_B :
			*valueRead = READ_BIT(PINB,pinNum);
			break;
		case IO_PORT_C :
			*valueRead = READ_BIT(PINC,pinNum);
			break;
		case IO_PORT_D :
			*valueRead = READ_BIT(PIND,pinNum);
			break;
		default:
			return DIO_INVALID_PORT;
		break;
	}
	/* Return OK if there is no error */
	return DIO_OK;
}