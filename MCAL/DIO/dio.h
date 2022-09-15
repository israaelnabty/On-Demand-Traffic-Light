/*
 * dio.h
 *
 * Created: 8/31/2022 4:57:39 PM
 *  Author: Israa
 */ 


#ifndef DIO_H_
#define DIO_H_

/* Included Files */
#include "../../Utilities/common_types.h"
#include "../../Utilities/bit_manipulations.h"
#include "../../MCU/MCU_registers.h"

/* Defined Macros */
/* Port Names in Letters */
#define IO_PORT_A 'A'
#define IO_PORT_B 'B'
#define IO_PORT_C 'C'
#define IO_PORT_D 'D'

/* Pins direction */
#define INPUT_PIN 0
#define OUTPUT_PIN 1 

/* Maximum Pins Number in Each Port */
#define IO_MAX_NUM_PIN 8

/* Pins Data */
#define LOW 0
#define HIGH 1

/* Defining Types */
	/* Error Handling */
typedef enum EN_DIO_error
{
	DIO_OK, DIO_INVALID_PORT, DIO_INVALID_PIN, DIO_INVALID_DIRECTION, DIO_INVALID_OUTPUT	
} EN_DIO_error_t;
 
/* Functions Prototypes */
/* Pins Initialization */
EN_DIO_error_t DIO_init(uint8_t portRegist, uint8_t pinNum, uint8_t pinDirection);

/* Pin Write */
EN_DIO_error_t DIO_write(uint8_t portRegist, uint8_t pinNum, uint8_t valueWrite);

/* Pin Toggle */
EN_DIO_error_t DIO_toggle(uint8_t portRegist, uint8_t pinNum);

/* Pin Read */
EN_DIO_error_t DIO_read(uint8_t portRegist, uint8_t pinNum, uint8_t* valueRead);

#endif /* DIO_H_ */