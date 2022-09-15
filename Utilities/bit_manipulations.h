/*
 * bitManipulations.h
 * Dealing with a Specific Bit in a Register
 * Created: 9/1/2022 7:26:25 AM
 *  Author: Israa
 */ 

#ifndef BIT_MANIPULATIONS_H_
#define BIT_MANIPULATIONS_H_

/* Defined Function-like Macros */
/* Set a Bit in a Register */
#define SET_BIT(REG,BIT_NO) (REG |= (1<<BIT_NO))

/* Clear a Bit in a Register */
#define CLEAR_BIT(REG,BIT_NO) (REG &= ~(1<<BIT_NO))

/* Toggle a Bit in a Register */
#define TOGGLE_BIT(REG,BIT_NO) (REG ^= (1<<BIT_NO))

/* Read a Bit in a Register */
#define READ_BIT(REG,BIT_NO) ((REG & (1 << BIT_NO)) >> BIT_NO)


#endif /* BITMANIPULATIONS_H_ */