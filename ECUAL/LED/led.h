/*
 * led.h
 *
 * Created: 8/31/2022 9:17:28 PM
 *  Author: Israa
 */ 


#ifndef LED_H_
#define LED_H_

/* Included Files */
#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/TIMER/timer0.h"

/* Defined Macros */
/* Used LED Ports and Pins */
/* Cars LEDs */
#define LED1_PORT IO_PORT_A
#define LED1_PIN 0

#define LED2_PORT IO_PORT_A
#define LED2_PIN 1

#define LED3_PORT IO_PORT_A
#define LED3_PIN 2

/* Pedestrian LEDs */
#define LED4_PORT IO_PORT_B
#define LED4_PIN 0

#define LED5_PORT IO_PORT_B
#define LED5_PIN 1

#define LED6_PORT IO_PORT_B
#define LED6_PIN 2

/* Defining Types */
	/* Error Handling */
typedef enum EN_LED_error
{
	LED_OK, LED_INVALID_PORT, LED_INVALID_PIN, LED_INVALID_OUTPUT
} EN_LED_error_t;


/* Define Global Variables */
extern uint8_t stopBlinkLED;
extern uint8_t stopMultiBlinkLED;

/* Functions Prototypes */
/* LED Pins Initialization */
EN_LED_error_t LED_init(uint8_t portLED, uint8_t pinNum);

/* LED On */
EN_LED_error_t LED_on(uint8_t portLED, uint8_t pinNum);

/* LED Off */
EN_LED_error_t LED_off(uint8_t portLED, uint8_t pinNum);

/* LED Toggle */
EN_LED_error_t LED_toggle(uint8_t portLED, uint8_t pinNum);

/* LED Blink */
EN_LED_error_t LED_blink(uint8_t portLED, uint8_t pinNum, float timeBlink_ms);

/* Multiple LEDs Blink */
EN_LED_error_t LED_blinkMultiple(uint8_t* portLED, uint8_t* pinNum, uint8_t numOfLEDs, float timeBlink_ms);

#endif /* LED_H_ */