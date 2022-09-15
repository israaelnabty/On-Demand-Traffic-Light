/*
 * registers.h
 * All the Microcontroller Registers Defined By Their Addresses
 * Created: 8/31/2022 9:16:16 PM
 *  Author: Israa
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

/* Included Files*/
#include "../Utilities/common_types.h"

/* Defined Macros */
/************************************************************************/
/*                       General MCU Registers                          */
/************************************************************************/
#define SREG (*((volatile uint8_t*)0x5F))
#define MCUCR (*((volatile uint8_t*)0x55))
#define MCUCSR (*((volatile uint8_t*)0x54))
#define SFIOR (*((volatile uint8_t*)0x50))
/************************************************************************/
/*                            DIO Registers                             */
/************************************************************************/
#define PORTA (*((volatile uint8_t*)0x3B))
#define DDRA (*((volatile uint8_t*)0x3A))
#define PINA (*((volatile uint8_t*)0x39))

#define PORTB (*((volatile uint8_t*)0x38))
#define DDRB (*((volatile uint8_t*)0x37))
#define PINB (*((volatile uint8_t*)0x36))

#define PORTC (*((volatile uint8_t*)0x35))
#define DDRC (*((volatile uint8_t*)0x34))
#define PINC (*((volatile uint8_t*)0x33))

#define PORTD (*((volatile uint8_t*)0x32))
#define DDRD (*((volatile uint8_t*)0x31))
#define PIND (*((volatile uint8_t*)0x30))
/************************************************************************/
/*                          TIMERS Registers                            */
/************************************************************************/
/* Timer0 Registers */
#define OCR0 (*((volatile uint8_t*)0x5C))
#define TCCR0 (*((volatile uint8_t*)0x53))
#define TCNT0 (*((volatile uint8_t*)0x52))
/************************************************************************/
/*                        Interrupt Registers                           */
/************************************************************************/
/* Timers Interrupt Registers */
#define TIMSK (*((volatile uint8_t*)0x59))
#define TIFR (*((volatile uint8_t*)0x58))
/* External Interrupt Registers */
#define GICR (*((volatile uint8_t*)0x5B))
#define GIFR (*((volatile uint8_t*)0x5A))
/************************************************************************/
/*                           ADC Registers                              */
/************************************************************************/
#define ADMUX (*((volatile uint8_t*)0x27))
#define ADCSRA (*((volatile uint8_t*)0x26))
#define ADCH (*((volatile uint8_t*)0x25))
#define ADCL (*((volatile uint8_t*)0x24))


#endif /* REGISTERS_H_ */