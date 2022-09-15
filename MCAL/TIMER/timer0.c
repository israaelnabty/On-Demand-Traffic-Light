/*
 * timer0.c
 *
 * Created: 8/31/2022 4:58:10 PM
 *  Author: Israa
 */ 

/* Included Files */
#include "timer0.h"

/* Define Global Variables */
	/* Pointer to function (callback function, called in ISRs) */
void (*ptr_callbackFunction_overflow)(void) = NULL;
void (*ptr_callbackFunction_CTC)(void) = NULL;
	/* The overflows counter */
uint8_t initialTimerVal = 0; /* Used each time an overflow occurs to start next overflow phase */
uint16_t delayOverflows = 1; /* Generated From Delay Calculations */
volatile uint16_t overflowCount = 0; /* Changed due to hardware */


/* Functions Definitions */
/* Timer0 Initialization */
void TIMER0_overflowMode_init(uint8_t initialTimerVal, uint8_t enableInterrupt)
{
	/* Select Normal Mode
	*  Select No Clock Source */
	TCCR0 = 0;
	/* Set the Timer0 Initial Value*/
	TIMER0_setInitialValue(initialTimerVal);
	/* Enable or Disable Interrupt */
	TIMER0_interruptControl(OVERFLOW_MODE, enableInterrupt);
}

EN_TIMER0_error_t TIMER0_CTC_init(uint8_t outWaveform, uint8_t compVal, uint8_t enableInterrupt)
{
	/* Reset the Timer0 Control Register
	*  Select No Clock Source */
	TCCR0 = 0;
	/* Select CTC Mode */
	CLEAR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	/* Select CTC Output Waveform on the "Output" Pin OC0 */
	switch (outWaveform)
	{
		case TOGGLE_ON_COMP_MATCH: /* Generating a waveform */
			SET_BIT(TCCR0,4);
			CLEAR_BIT(TCCR0,5);
		break;
		case CLEAR_ON_COMP_MATCH:
			CLEAR_BIT(TCCR0,4);
			SET_BIT(TCCR0,5);	   
		break;
		case SET_ON_COMP_MATCH:
			SET_BIT(TCCR0,4);
			SET_BIT(TCCR0,5);
		break;
		default:
			return TIMER0_INVALID_OUT_WAVEFORM;
	}
	/* Set the Timer0 Compare Register Value */
	TIMER0_setOutCompareValue(compVal);
	/* Enable or Disable Interrupt */
	TIMER0_interruptControl(CTC_MODE, enableInterrupt);
	/* Return OK if there is no error */
	return TIMER0_OK;
}

EN_TIMER0_error_t TIMER0_PWM_init(uint8_t PWMMode, uint8_t outWaveform, uint8_t compVal)
{
	/* Reset the Timer0 Control Register
	*  Select No Clock Source */
	TCCR0 = 0;
	/* Select PWM Mode: Fast or Phase Correct */
	SET_BIT(TCCR0,6);
	switch (PWMMode)
	{
		case FAST_PWM_MODE:
			SET_BIT(TCCR0,3);
		break;
		case PHASE_CORR_PWM_MODE:
			CLEAR_BIT(TCCR0,3);
		break;
		default:
			return TIMER0_INVALID_MODE;
	}
	/* Select PWM Output Waveform on the "Output" Pin OC0 */	
	SET_BIT(TCCR0,5);
	switch (outWaveform)
	{
		case PWM_NON_INVERT:
			CLEAR_BIT(TCCR0,4);
		break;
		case PWM_INVERT:
			SET_BIT(TCCR0,4);
		break;
		default:
			return TIMER0_INVALID_OUT_WAVEFORM;
	}
	/* Set the Timer0 Compare Register Value */
	TIMER0_setOutCompareValue(compVal);
	/* Return OK if there is no error */
	return TIMER0_OK;
}


/* Timer0 Set Initial Value */
void TIMER0_setInitialValue(uint8_t initialVal)
{
	TCNT0 = initialVal;
}

/* Timer0 Set Output Compare Register */
void TIMER0_setOutCompareValue(uint8_t compareValue)
{
	OCR0 = compareValue;
}

/* Timer0 Force Compare Match 
 * (change the output as if an actual compare match occurs, but has no effect on flags or timer registers) */
void Timer0_CTCforceCompareMatch(void)
{
	SET_BIT(TCCR0,7);
}

/* Timer0 Start */
EN_TIMER0_error_t TIMER0_start(uint16_t clockSource)
{
	/* Enable a clock source: a prescaler or external source */
	switch (clockSource)
	{
		case PRESCALER_1:
			SET_BIT(TCCR0,0);
			CLEAR_BIT(TCCR0,1);
			CLEAR_BIT(TCCR0,2);
		break;
		case PRESCALER_8:
			CLEAR_BIT(TCCR0,0);
			SET_BIT(TCCR0,1);
			CLEAR_BIT(TCCR0,2);
		break;
		case PRESCALER_64:
			SET_BIT(TCCR0,0);
			SET_BIT(TCCR0,1);
			CLEAR_BIT(TCCR0,2);
		break;
		case PRESCALER_256:
			CLEAR_BIT(TCCR0,0);
			CLEAR_BIT(TCCR0,1);
			SET_BIT(TCCR0,2);
		break;
		case PRESCALER_1024:
			SET_BIT(TCCR0,0);
			CLEAR_BIT(TCCR0,1);
			SET_BIT(TCCR0,2);
		break;
		case EXT_CLOCK_FALLING:
			CLEAR_BIT(TCCR0,0);
			SET_BIT(TCCR0,1);
			SET_BIT(TCCR0,2);
		break;
		case EXT_CLOCK_RISING:
			SET_BIT(TCCR0,0);
			SET_BIT(TCCR0,1);
			SET_BIT(TCCR0,2);
		break;
		default:
			return TIMER0_INVALID_CLOCK;
	}
	/* Return OK if there is no error */
	return TIMER0_OK;
}

/* Timer0 Stop */
void TIMER0_stop(void)
{
	/* Disable Clock Source */
	CLEAR_BIT(TCCR0,0);
	CLEAR_BIT(TCCR0,1);
	CLEAR_BIT(TCCR0,2);
}

/* Timer0 Get Timer Flag State (Polling case or Busy Waiting) */
EN_TIMER0_error_t TIMER0_getFlagStatus(uint8_t timerMode, uint8_t* valueRead)
{
	/* Read the flag, and if the flag is 1, clear it by setting it */
	switch (timerMode)
	{
		case OVERFLOW_MODE:
			*valueRead = READ_BIT(TIFR,0);
			if ((*valueRead) == 1)
			{
				SET_BIT(TIFR,0);
			}
		break;
		case CTC_MODE:
			*valueRead = READ_BIT(TIFR,1);
			if ((*valueRead) == 1)
			{
				SET_BIT(TIFR,1);
			}
		break;
		default:
			return TIMER0_INVALID_MODE;
	}
	/* Return OK if there is no error */
	return TIMER0_OK;
}

/* Timer0 Enable/Disable Interrupt */
EN_TIMER0_error_t TIMER0_interruptControl(uint8_t timerMode, uint8_t enableInterrupt)
{
	/* Enable or Disable Interrupt */
	if(enableInterrupt == 1)
	{
		switch(timerMode)
		{
			case OVERFLOW_MODE:
				SET_BIT(TIMSK,0);
			break;
			case CTC_MODE:
				SET_BIT(TIMSK,1);
			break;
			default:
				return TIMER0_INVALID_MODE;
		}		
	}
	else
	{
		switch(timerMode)
		{
			case OVERFLOW_MODE:
				CLEAR_BIT(TIMSK,0);
			break;
			case CTC_MODE:
			    CLEAR_BIT(TIMSK,1);
			break;
			default:
				return TIMER0_INVALID_MODE;
		}
	}
	/* Return OK if there is no error */
	return TIMER0_OK;
}

/* Timer0 Delay Function (in milliseconds) */
void TIMER0_delay_ms(float delayValue_ms)
{
	/* Get the Current Suitable Prescaler Value */
	uint16_t overflowPrescalerVal;
	TIMER0_setPrescaler(delayValue_ms, &overflowPrescalerVal);
	
	/* Calculate the max delay by one timer overflow */
	float tickTime_ms = (overflowPrescalerVal/(F_CPU/1000.0));
	float maxDelayPerOverflow_ms = tickTime_ms*256; /* 256 refers to the timer no. of bits */
	uint16_t ticksPerOverflow;
	
	/* Calculate Initial Timer Value and number of required overflows */
	if (delayValue_ms <= maxDelayPerOverflow_ms)
	{
		/* Require No. of overflows is 1 */
		delayOverflows = 1;
		/* Calculate the initial timer value */
		initialTimerVal = (uint8_t)((maxDelayPerOverflow_ms - delayValue_ms)/tickTime_ms);		
	} 
	else
	{
		/* Calculate the number of overflows required */
		delayOverflows = (uint16_t)((delayValue_ms/maxDelayPerOverflow_ms) + 0.5);
		/* Calculate the initial timer value, rounding to the nearest integer */
		ticksPerOverflow = (uint16_t)(((delayValue_ms/tickTime_ms)/(float)(delayOverflows)) + 0.5);
		if (ticksPerOverflow >= 256)
		{
			initialTimerVal = 0;
		} 
		else
		{
			initialTimerVal = (uint8_t)(256 - ticksPerOverflow);
		}		
	}
	
	/* Initialize Timer0 in the overflow mode, Give it initial value and Enable its Interrupt */
	TIMER0_overflowMode_init(initialTimerVal,1);
    /* Enable Global Interrupt */
	sei();
	/* Clear the overflows counter */
	overflowCount = 0;
	/* Start Timing */
	
	TIMER0_start(overflowPrescalerVal);
	/* Next step in the code: Busy Wait, Poll or Go ahead into code till an interrupt occurs */
}

/* Calculate timer0 required prescaler for a certain delay */
void TIMER0_setPrescaler(float delayTime_ms, uint16_t* prescalVal)
{
	/* For calculate tick times for each prescaler value */
	uint16_t prescalerValue[5] = {PRESCALER_1, PRESCALER_8, PRESCALER_64, PRESCALER_256, PRESCALER_1024};
	float frequencyCPU_kHz = F_CPU/1000.0;
	float tickTime_ms[5] = {prescalerValue[0]/frequencyCPU_kHz, 
		                    prescalerValue[1]/frequencyCPU_kHz, 
						    prescalerValue[2]/frequencyCPU_kHz,
						    prescalerValue[3]/frequencyCPU_kHz,
						    prescalerValue[4]/frequencyCPU_kHz};
						  
	/* Tick Time should not exceed delay time*/
	for (uint8_t index = 4; index >= 0; index--)
	{
		if (delayTime_ms >= tickTime_ms[index])
		{
			*prescalVal = prescalerValue[index]; 
			break;
		}
		/* In case we reach here at index 0, take the min prescaler value */
		if (index == 0)
		{
			*prescalVal = prescalerValue[0];
		}
	}
}

/* A function that check if the current delay has finished or not */
uint8_t TIMER0_isDelayFinished(void)
{
	/* Checking the current overflow counts in the timer0 */
	if (overflowCount < delayOverflows)
	{
		return 0;
	} 
	else 
	{
		return 1;
	}
}

/* A function that sets the pointer to a callback function (for overflow ISR) */
EN_TIMER0_error_t TIMER0_setCallbackFunc(uint8_t timerMode, void(*ptr_func)(void))
{
	switch(timerMode)
	{
		case OVERFLOW_MODE:
			ptr_callbackFunction_overflow = ptr_func;
		break;
		case CTC_MODE:
			ptr_callbackFunction_CTC = ptr_func;
		break;
		default:
			return TIMER0_INVALID_MODE;
	}	
	/* Return OK if there is no error */
	return TIMER0_OK;
}

/* ISR Definition of Timer0 Interrupts */
ISR(TIMER_OVF_0)
{
	/* Count the overflows */
	overflowCount++;
	/* Check if max. number of overflows is reached, otherwise set the next overflows initial timer value */
	if (overflowCount < delayOverflows)
	{
		TIMER0_setInitialValue(initialTimerVal);
	}
	else if (overflowCount == delayOverflows)
	{
		/* Stop Timer0 (if needed) */		
		TIMER0_stop();		
		/* Execute any required (callBack) function */
		if(ptr_callbackFunction_overflow != NULL)
		{
			/* Execute Callback Function Using a Function Pointer */
			(*ptr_callbackFunction_overflow)();
		}
	}
}

ISR(TIMER_CTC_0)
{
	/* Write Your ISR here */
	if(ptr_callbackFunction_CTC != NULL)
	{
		/* Execute Callback Function Using a Function Pointer */
		(*ptr_callbackFunction_CTC)();
	}
}