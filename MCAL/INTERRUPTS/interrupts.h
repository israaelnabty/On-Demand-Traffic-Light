/*
 * interrupt.h
 *
 * Created: 8/31/2022 4:58:48 PM
 *  Author: Israa
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/* Macros definitions */
/* Defining Interrupt Vectors */
	/* External Interrupt Requests (0,1,2) */
#define EXT_INT_0 __vector_1
#define EXT_INT_1 __vector_2
#define EXT_INT_2 __vector_3
	/* Timer Interrupt Requests */
/* Timer 2 */
#define TIMER_CTC_2 __vector_4
#define TIMER_OVF_2 __vector_5
/* Timer 1 */
#define TIMER_CAPT_1 __vector_6
#define TIMER_CTC_1A __vector_7
#define TIMER_CTC_1B __vector_8
#define TIMER_OVF_1 __vector_9
/* Timer 0 */
#define TIMER_CTC_0 __vector_10
#define TIMER_OVF_0 __vector_11
	/* Communications Protocols */
#define SPI_STC __vector_12
#define USART_RXC __vector_13
#define USART_UDRE __vector_14
#define USART_TXC __vector_15
#define TWI __vector_19
	/* ADC Conversion Complete */
#define ADC_COMPLETE __vector_16
	/* Analog Comparators */
#define ANA_COMP __vector_18
	/* Memories */
/* EEPROM Ready */
#define EE_RDY __vector_17        
/*  Store Program Memory Ready */
#define SPM_READY __vector_20


/* Define the assembly of setting the global interrupt (I-bit in SREG) */
#define sei() __asm__ __volatile__ ("sei" ::: "memory")

/* Define the assembly of clearing the global interrupt (I-bit in SREG) */
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

/* Defining the ISRs Prototype and Definition Header */
#define ISR(INT_VECT) \
void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)

#endif /* INTERRUPT_H_ */