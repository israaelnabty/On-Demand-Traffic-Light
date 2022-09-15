/*
 * timer0.h
 *
 * Created: 8/31/2022 4:57:57 PM
 *  Author: Israa
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

/* Included Files */
#include "../../Utilities/common_types.h"
#include "../../Utilities/bit_manipulations.h"
#include "../../MCU/MCU_registers.h"
#include "../../MCU/MCU_config.h"
#include "../INTERRUPTS/interrupts.h"


/* Macros definitions */
	/* TIMER0 Modes */
#define OVERFLOW_MODE 0
#define CTC_MODE 1
#define FAST_PWM_MODE 2
#define PHASE_CORR_PWM_MODE 3
   
   /* CTC Mode - Waveform Output on the Pin OC0 */
#define TOGGLE_ON_COMP_MATCH 'T'   /* Generating a waveform */
#define CLEAR_ON_COMP_MATCH 'C'
#define SET_ON_COMP_MATCH 'S'

	/* PWM Mode - Waveform Output on the Pin OC0 */
#define PWM_NON_INVERT 'N'
#define PWM_INVERT 'I'

	/* TIMER0 Clock Sources */
#define PRESCALER_1 1
#define PRESCALER_8 8
#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024
#define EXT_CLOCK_FALLING 'F'
#define EXT_CLOCK_RISING 'R'

/* Defining Types */
	/* Error Handling */
typedef enum EN_TIMER0_error
{
	TIMER0_OK, TIMER0_INVALID_MODE, TIMER0_INVALID_OUT_WAVEFORM, TIMER0_INVALID_PRESCALER, TIMER0_INVALID_CLOCK
} EN_TIMER0_error_t;

/* Declare "extern" Global Variables */
	/* The overflows counter */
extern uint16_t delayOverflows; /* Generated From Delay Calculations */
extern volatile uint16_t overflowCount; /* Changed due to hardware */

/* Functions Prototypes */
	/* Timer0 Initialization */
void TIMER0_overflowMode_init(uint8_t initialTimerVal, uint8_t enableInterrupt);
EN_TIMER0_error_t TIMER0_CTC_init(uint8_t outWaveform, uint8_t compVal, uint8_t enableInterrupt);
EN_TIMER0_error_t TIMER0_PWM_init(uint8_t PWMMode, uint8_t outWaveform, uint8_t compVal);

	/* Timer0 Set Initial Value */
void TIMER0_setInitialValue(uint8_t initValue);

	/* Timer0 Set Output Compare Register */
void TIMER0_setOutCompareValue(uint8_t compareValue);

	/* Timer0 Force Compare Match 
	* (change the output as if an actual compare match occurs, but has no effect on flags or timer registers) */
void Timer0_CTCforceCompareMatch(void);

	/* Timer0 Start */
EN_TIMER0_error_t TIMER0_start(uint16_t prescalerValue);

	/* Timer0 Stop */
void TIMER0_stop(void);

	/* Timer0 Get Timer Flag State (Polling case or Busy Waiting) */
EN_TIMER0_error_t TIMER0_getFlagStatus(uint8_t timerMode, uint8_t* valueRead);

	/* Timer0 Enable/Disable Interrupt */
EN_TIMER0_error_t TIMER0_interruptControl(uint8_t timerMode, uint8_t enableInterrupt);

	/* Timer0 Delay Function (in milliseconds) */
void TIMER0_delay_ms(float delayValue_ms);

	/* Calculate timer0 required prescaler for a certain delay */
void TIMER0_setPrescaler(float delayTime_ms, uint16_t* prescalVal);

	/* A function that check if the current delay has finished or not */
uint8_t TIMER0_isDelayFinished(void);

	/* A function that sets the pointer to a callback function (for overflow ISR) */
EN_TIMER0_error_t TIMER0_setCallbackFunc(uint8_t timerMode, void(*ptr_func)(void));

#endif /* TIMER0_H_ */