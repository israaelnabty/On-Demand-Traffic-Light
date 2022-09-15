/*
 * application.c
 *
 * Created: 8/31/2022 4:56:29 PM
 *  Author: Israa
 */ 

/* Included Files */
#include "app.h"

/* Global Variables */
/* LEDs States */
uint8_t carsLedState;
uint8_t pedstrianLedState;
/* This Flag is set after executing "Pedestrian Mode" Function */
uint8_t isResetCarsMode = 0; 
/* This Flag Exits the Pedestrian Mode if it is called by external interrupt while its execution */
uint8_t ispedestrianModeExecution = 0; 

/* Functions Definitions */
/* Application Initialization */
void APP_init(void)
{
	/* LED initializations */
		/* Cars LEDs */
	LED_init(LED1_PORT,LED1_PIN); // Green
	LED_init(LED2_PORT,LED2_PIN); // Yellow
	LED_init(LED3_PORT,LED3_PIN); // Red
		/* Pedestrians LEDs */
	LED_init(LED4_PORT,LED4_PIN); // Green
	LED_init(LED5_PORT,LED5_PIN); // Yellow
	LED_init(LED6_PORT,LED6_PIN); // Red
	
	/* External Interrupt initializations */
		/* Pedestrian crosswalk Push Button */
		/* Interrupt works when the button is released */
	EXT_INTERRUPT0_init(INT0_FALLING_EDGE);	
	    /* Set the callback function of the external interrupt(0) ISR as the pedestrian mode function */
	EXT_INTERRUPT_setCallbackFunc(EXTERNAL_INT0, &APP_pedestrianMode);
}

/* Application Start */
void APP_start(void)
{
	while(1)
	{
		/* Normally, operate on the normal mode, till an external
		 * interrupt occurs on the pedestrian button */
		APP_carsMode();	
	}
}

/* Cars Mode */
void APP_carsMode(void)
{ 
	/* Initializing Cars Mode */
	/* Initialize Cars Mode Reset Flag with zero */
	isResetCarsMode = 0;
	/* Pedestrian LEDs should be off, except for the Red LED only */
	pedstrianLedState = PEDEST_RED_STATE;
	LED_off(LED4_PORT,LED4_PIN);
	LED_off(LED5_PORT,LED5_PIN);
	LED_on(LED6_PORT,LED6_PIN);
	
	/* Start the cars mode, with all cars LEDs off, except the Green LED only */
	/* Start States from Green */
	carsLedState = CARS_GREEN_STATE;
	LED_on(LED1_PORT,LED1_PIN);
	LED_off(LED2_PORT,LED2_PIN);
	LED_off(LED3_PORT,LED3_PIN);
	
	/* Set the change direction of Cars LEDs as FORWARD */
	uint8_t carsStateDirection = CARS_STATE_FORWARD;		
	
	/* Continue Changing LEDs Colors by the required sequence */
	while(1)
	{
		switch(carsLedState)
		{
			case CARS_GREEN_STATE:
				LED_on(LED1_PORT,LED1_PIN);
				/* SetTimer for 5 seconds */
				TIMER0_delay_ms(5000);
				/* Busy Wait for the timer0 end */
				while((TIMER0_isDelayFinished() != 1)&&(isResetCarsMode == 0));
				/* Exit the Normal Mode Function to be reentered from the application */
				if(isResetCarsMode == 1)
				{
					return;
				}
				LED_off(LED1_PORT,LED1_PIN);
				/* Transit to the next (yellow) state */
				carsLedState++;
				/* State FORWARD direction (green -> yellow -> red) */
				carsStateDirection = CARS_STATE_FORWARD;
			break;
			case CARS_YELLOW_STATE:
				/* Blink LED for 5 seconds */
				LED_blink(LED2_PORT,LED2_PIN,5000);
				/* Exit the Normal Mode Function to be reentered from the application */
				if(isResetCarsMode == 1)
				{
					return;
				}
				/* Transit to the next state */
				if (carsStateDirection == CARS_STATE_FORWARD)
				{
					/* Transit to the next (red) state */
					carsLedState++;
				}
				else
				{
					/* Transit to the previous (green) state */
					carsLedState--;
				}			
			break;
			case CARS_RED_STATE:
				LED_on(LED3_PORT,LED3_PIN);
				/* SetTimer For 5 seconds */
				TIMER0_delay_ms(5000);
				/* Busy Wait for the timer0 end */
				while((TIMER0_isDelayFinished() != 1)&&(isResetCarsMode == 0));
				/* Exit the Normal Mode Function to be reentered from the application */
				if(isResetCarsMode == 1)
				{
					return;
				}
				LED_off(LED3_PORT,LED3_PIN);
				/* Transit to the previous (yellow) state */
				carsLedState--;
				/* State BACKWARD direction (red -> yellow -> green) */
				carsStateDirection = CARS_STATE_BACKWARD;				
			break;			
		}
	}
}

/* Pedestrian Mode */
void APP_pedestrianMode(void)
{		
	/* Check if pedestrian Mode is currently executed */
	if (ispedestrianModeExecution == 1)
	{
		return;
	}
	
	/* Set pedestrian mode execution Flag as 1 */
	ispedestrianModeExecution = 1;
	
	/* Check the Cars LED Color */
	if(carsLedState == CARS_RED_STATE)
	{
		APP_pedestrianCross();
	}
	else /* Yellow or Green */
	{		
		APP_pedestrianReadyCross();
		APP_pedestrianCross();
	}
	
	APP_pedestrianReadyStop();
	APP_pedestrianStop();	
	
	/* Clear pedestrian mode execution Flag to enable next execution */
	ispedestrianModeExecution = 0;
	
	/* Set Cars Mode Reset Flag */
	isResetCarsMode = 1;
}

/* Pedestrian Ready Cross */
void APP_pedestrianReadyCross(void)
{
	if(carsLedState == CARS_YELLOW_STATE)
	{
		/* Enable Stop Yellow Blink When Returning to Blinking Function Context After Interrupt */
		stopBlinkLED = 1;
		/* Turn off Cars Yellow LED (if interrupt occurs when it is on) */
		LED_off(LED1_PORT,LED1_PIN);
		LED_off(LED2_PORT,LED2_PIN);
		LED_off(LED3_PORT,LED3_PIN);
	}
	else if (carsLedState == CARS_GREEN_STATE)
	{
		/* Turn off Cars Green LED */
		LED_off(LED1_PORT,LED1_PIN);
		LED_off(LED2_PORT,LED2_PIN);
		LED_off(LED3_PORT,LED3_PIN);
	}
	
	/* Keep the Red Pedestrian LED on */
	LED_off(LED4_PORT,LED4_PIN);
	LED_off(LED5_PORT,LED5_PIN);
	LED_on(LED6_PORT,LED6_PIN);
	
	/* Blink Cars and Pedestrian Yellow LEDs for 5 seconds */
	/* Assign the two yellow LEDs as Blinking LEDs */
	uint8_t ledPortsArrayBlink[2] = {LED2_PORT,LED5_PORT};
	uint8_t ledPinsArrayBlink[2] = {LED2_PIN,LED5_PIN};
	carsLedState = CARS_YELLOW_STATE;
	pedstrianLedState = PEDEST_RED_YELLOW_STATE;
	LED_blinkMultiple(ledPortsArrayBlink, ledPinsArrayBlink, 2, 5000);
}

/* Pedestrian Cross */
void APP_pedestrianCross(void)
{
	/* Keep Cars Red LED State On */
	carsLedState = CARS_RED_STATE;	
	LED_off(LED1_PORT,LED1_PIN);
	LED_off(LED2_PORT,LED2_PIN);
	LED_on(LED3_PORT,LED3_PIN);	
	
	/* Turn on the Green Pedestrian LED, while others are off */
	pedstrianLedState = PEDEST_GREEN_STATE;
	LED_on(LED4_PORT,LED4_PIN);
	LED_off(LED5_PORT,LED5_PIN);
	LED_off(LED6_PORT,LED6_PIN);
	
	/* SetTimer For 5 seconds */
	TIMER0_delay_ms(5000);
	/* Busy Wait for the timer0 end */
	while(overflowCount != delayOverflows);
}

/* Pedestrian Ready Stop */
void APP_pedestrianReadyStop(void)
{
	/* Keep Pedestrian Green LED State On, then Blink Yellow LED with Cars Yellow LED */
	pedstrianLedState = PEDEST_GREEN_YELLOW_STATE;
	LED_on(LED4_PORT,LED4_PIN);
	LED_off(LED5_PORT,LED5_PIN);
	LED_off(LED6_PORT,LED6_PIN);
	
	/* Turn off Cars Red LED */
	carsLedState = CARS_YELLOW_STATE;
	LED_off(LED1_PORT,LED1_PIN);
	LED_off(LED2_PORT,LED2_PIN);
	LED_off(LED3_PORT,LED3_PIN);
	
	/* Blink Cars and Pedestrian Yellow LEDs for 5 seconds */
	/* Assign the two yellow LEDs as Blinking LEDs */
	uint8_t ledPortsArrayBlink[2] = {LED2_PORT,LED5_PORT};
	uint8_t ledPinsArrayBlink[2] = {LED2_PIN,LED5_PIN};
	LED_blinkMultiple(ledPortsArrayBlink, ledPinsArrayBlink, 2, 5000);
}

/* Pedestrian Stop */
void APP_pedestrianStop(void)
{
	/* Turn on the Red Pedestrian LED, and Turn off the Green Pedestrian LED */
	pedstrianLedState = PEDEST_RED_STATE;
	LED_off(LED4_PORT,LED4_PIN);
	LED_off(LED5_PORT,LED5_PIN);
	//LED_on(LED6_PORT,LED6_PIN);
	
	/* Turn on Cars Green LED only, then return to the calling function (normal mode) */
	carsLedState = CARS_GREEN_STATE;
	//LED_on(LED1_PORT,LED1_PIN);
	LED_off(LED2_PORT,LED2_PIN);
	LED_off(LED3_PORT,LED3_PIN);
}
