/*
 * push_button.h
 *
 * Created: 8/31/2022 4:59:35 PM
 *  Author: Israa
 */ 


#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

/* Included Files */
#include "../../MCAL/DIO/dio.h"

/* Defined Macros */
	/* Used Push Buttons Ports and Pins */
	/* Pedestrian Push Button */
#define PBUTT1_PORT IO_PORT_D
#define PBUTT1_PIN 2

	/* States of Push Button */
	/* Using Pull-Down Configuration */
#define PBUTT_RELEASED 0
#define PBUTT_PRESSED 1

/* Defining Types */
	/* Error Handling */
typedef enum EN_PBUTT_error
{
	PBUTT_OK, PBUTT_INVALID_PORT, PBUTT_INVALID_PIN
} EN_PBUTT_error_t;

/* Functions Prototypes */
	/* Push Button Pins Initialization */
EN_PBUTT_error_t PBUTTON_init(uint8_t portBUTT, uint8_t pinNum);

	/* Read Push Button */
EN_PBUTT_error_t PBUTTON_read(uint8_t portBUTT, uint8_t pinNum, uint8_t* valueRead);


#endif /* PUSH_BUTTON_H_ */