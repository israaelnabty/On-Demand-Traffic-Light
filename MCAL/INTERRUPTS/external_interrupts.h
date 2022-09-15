/*
 * external_interrupts.h
 *
 * Created: 9/3/2022 8:40:41 AM
 *  Author: Israa
 */ 


#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

/* Included Files */
#include "interrupts.h"
#include "../../Utilities/common_types.h"
#include "../../Utilities/bit_manipulations.h"
#include "../../MCU/MCU_registers.h"


/* Macros definitions */
	/* External Interrupt Names */
#define EXTERNAL_INT0 0
#define EXTERNAL_INT1 1
#define EXTERNAL_INT2 2

	/* Interrupt Trigger Sense Control */
#define INT0_LOW_LEVEL 'L'
#define INT0_ANY_LOGIC_CHANGE 'A'
#define INT0_FALLING_EDGE 'F'
#define INT0_RISING_EDGE 'R'

#define INT1_LOW_LEVEL 'L'
#define INT1_ANY_LOGIC_CHANGE 'A'
#define INT1_FALLING_EDGE 'F'
#define INT1_RISING_EDGE 'R'

#define INT2_FALLING_EDGE 'F'
#define INT2_RISING_EDGE 'R'

/* Defining Types */
	/* Error Handling */
typedef enum EN_EXT_INT_error
{
	EXT_INT_OK, EXT_INT_INVALID_TRIG_SENSE, EXT_INT_INVALID_INT_NUM
} EN_EXT_INT_error_t;

/* Functions Prototypes */
/* Initialize External Interrupts: select trigger sense, then enables */
EN_EXT_INT_error_t EXT_INTERRUPT0_init(uint8_t triggerSense);
EN_EXT_INT_error_t EXT_INTERRUPT1_init(uint8_t triggerSense);
EN_EXT_INT_error_t EXT_INTERRUPT2_init(uint8_t triggerSense);

/* Disable External Interrupts */
EN_EXT_INT_error_t EXT_INTERRUPT_disable(uint8_t interruptNum);

/* Read External Interrupt Flags (Polling case or Busy Waiting) */
EN_EXT_INT_error_t EXT_INTERRUPT_getFlagStatus(uint8_t interruptNum, uint8_t* valueRead);

/* A function that sets the pointer to a callback function (for ISRs) */
EN_EXT_INT_error_t EXT_INTERRUPT_setCallbackFunc(uint8_t interruptNum, void(*ptr_func)(void));

#endif /* EXTERNAL_INTERRUPTS_H_ */