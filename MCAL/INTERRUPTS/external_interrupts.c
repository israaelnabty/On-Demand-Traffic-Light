/*
 * external_interrupts.c
 *
 * Created: 9/3/2022 8:41:00 AM
 *  Author: Israa
 */ 

/* Included Files */
#include "external_interrupts.h"

/* Define Global Variables */
	/* Three Pointers to function (callback function, called in ISRs) */
void (*ptr_callbackFunction_externalInt[3])(void) = {NULL};
	
/* Functions Definitions */
/* Initialize External Interrupts: select trigger sense, then enables */
EN_EXT_INT_error_t EXT_INTERRUPT0_init(uint8_t triggerSense)
{
	/* Select Trigger Sense */
	switch (triggerSense)
	{
	case INT0_LOW_LEVEL:
		CLEAR_BIT(MCUCR,0);
		CLEAR_BIT(MCUCR,1);
	break;
	case INT0_ANY_LOGIC_CHANGE:
		SET_BIT(MCUCR,0);
		CLEAR_BIT(MCUCR,1);
	break;
	case INT0_FALLING_EDGE:
		CLEAR_BIT(MCUCR,0);
		SET_BIT(MCUCR,1);
	break;
	case INT0_RISING_EDGE:
		SET_BIT(MCUCR,0);
		SET_BIT(MCUCR,1);
	break;
	default:
		return EXT_INT_INVALID_TRIG_SENSE;
	}
	/* Enable External Interrupt 0 */
	SET_BIT(GICR,6);	
	/* Enable Global Interrupt */
	sei();
	/* Return OK if there is no error */
	return EXT_INT_OK;
}

EN_EXT_INT_error_t EXT_INTERRUPT1_init(uint8_t triggerSense)
{
	/* Select Trigger Sense */
	switch (triggerSense)
	{
		case INT1_LOW_LEVEL:
			CLEAR_BIT(MCUCR,2);
			CLEAR_BIT(MCUCR,3);
		break;
		case INT1_ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,2);
			CLEAR_BIT(MCUCR,3);
		break;
		case INT1_FALLING_EDGE:
			CLEAR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		break;
		case INT1_RISING_EDGE:
			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		break;
		default:
			return EXT_INT_INVALID_TRIG_SENSE;
	}
	/* Enable External Interrupt 1 */
	SET_BIT(GICR,7);
	/* Enable Global Interrupt */
	sei();
	/* Return OK if there is no error */
	return EXT_INT_OK;
}
EN_EXT_INT_error_t EXT_INTERRUPT2_init(uint8_t triggerSense)
{
	/* Select Trigger Sense */
	switch (triggerSense)
	{
		case INT2_FALLING_EDGE:
			CLEAR_BIT(MCUCSR,6);
		break;
		case INT2_RISING_EDGE:
			SET_BIT(MCUCSR,6);
		break;
		default:
			return EXT_INT_INVALID_TRIG_SENSE;
	}
	/* Enable External Interrupt 2 */
	SET_BIT(GICR,5);
	/* Enable Global Interrupt */
	sei();
	/* Return OK if there is no error */
	return EXT_INT_OK;
}

/* Disable External Interrupts */
EN_EXT_INT_error_t EXT_INTERRUPT_disable(uint8_t interruptNum)
{
	switch (interruptNum)
	{
	case EXTERNAL_INT0:
		CLEAR_BIT(GICR,6);
	break;
	case EXTERNAL_INT1:
		CLEAR_BIT(GICR,7);
	break;
	case EXTERNAL_INT2:
		CLEAR_BIT(GICR,5);
	break;
	default:
		return EXT_INT_INVALID_INT_NUM;
	}
	/* Return OK if there is no error */
	return EXT_INT_OK;
}

/* Read External Interrupt Flags (Polling case or Busy Waiting) */
EN_EXT_INT_error_t EXT_INTERRUPT_getFlagStatus(uint8_t interruptNum, uint8_t* valueRead)
{
	/* Read the flag, and if the flag is 1, clear it by setting it */
	switch (interruptNum)
	{
		case EXTERNAL_INT0:
			*valueRead = READ_BIT(GIFR,6);
			if ((*valueRead) == 1)
			{
				SET_BIT(GIFR,6);
			}
		break;
		case EXTERNAL_INT1:
			*valueRead = READ_BIT(GIFR,7);
			if ((*valueRead) == 1)
			{
				SET_BIT(GIFR,7);
			}
		break;
		case EXTERNAL_INT2:
			*valueRead = READ_BIT(GIFR,5);
			if ((*valueRead) == 1)
			{
				SET_BIT(GIFR,5);
			}
		break;
		default:
			return EXT_INT_INVALID_INT_NUM;
	}
	/* Return OK if there is no error */
	return EXT_INT_OK;
}

/* A function that sets the pointer to a callback function (for ISRs) */
EN_EXT_INT_error_t EXT_INTERRUPT_setCallbackFunc(uint8_t interruptNum, void(*ptr_func)(void))
{
	switch(interruptNum)
	{
		case EXTERNAL_INT0:
			ptr_callbackFunction_externalInt[0] = ptr_func;
		break;
		case EXTERNAL_INT1:
			ptr_callbackFunction_externalInt[1] = ptr_func;
		break;
		case EXTERNAL_INT2:
			ptr_callbackFunction_externalInt[2] = ptr_func;
		break;
		default:
			return EXT_INT_INVALID_INT_NUM;
	}
	/* Return OK if there is no error */
	return EXT_INT_OK;
}

/* ISR Definition of External Interrupts */
ISR(EXT_INT_0)
{
	/* Implement Your ISR */
	if(ptr_callbackFunction_externalInt[0] != NULL)
	{
		/* Execute Callback Function Using a Function Pointer */
		(*ptr_callbackFunction_externalInt[0])();
	}
}

ISR(EXT_INT_1)
{
	/* Implement Your ISR */
	if(ptr_callbackFunction_externalInt[1] != NULL)
	{
		/* Execute Callback Function Using a Function Pointer */
		(*ptr_callbackFunction_externalInt[1])();
	}
}

ISR(EXT_INT_2)
{
	/* Implement Your ISR */
	if(ptr_callbackFunction_externalInt[2] != NULL)
	{
		/* Execute Callback Function Using a Function Pointer */
		(*ptr_callbackFunction_externalInt[2])();
	}
}
