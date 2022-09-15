/*
 * application.h
 *
 * Created: 8/31/2022 4:56:48 PM
 *  Author: Israa
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

/* Included Files */
#include "../MCAL/DIO/dio.h"
#include "../MCAL/INTERRUPTS/external_interrupts.h"
#include "../ECUAL/LED/led.h"
#include "../ECUAL/PUSH BUTTON/push_button.h"

/* Defined Macros */
	/* Cars Mode */
#define CARS_GREEN_STATE 0
#define CARS_YELLOW_STATE 1
#define CARS_RED_STATE 2
    /* Cars Mode State Direction */
#define CARS_STATE_FORWARD 0
#define CARS_STATE_BACKWARD 1
	/* Pedestrian Mode */
#define PEDEST_GREEN_STATE 0
#define PEDEST_YELLOW_STATE 1
#define PEDEST_RED_STATE 2
#define PEDEST_GREEN_YELLOW_STATE 3
#define PEDEST_RED_YELLOW_STATE 4

/* Functions Prototypes */
/* Application Initialization */
void APP_init(void);

/* Application Start */
void APP_start(void);

/* Cars Mode */
void APP_carsMode(void);

/* Pedestrian Mode */
void APP_pedestrianMode(void);

/* Pedestrian Ready Cross */
void APP_pedestrianReadyCross(void);

/* Pedestrian Cross */
void APP_pedestrianCross(void);

/* Pedestrian Ready Stop */
void APP_pedestrianReadyStop(void);

/* Pedestrian Stop */
void APP_pedestrianStop(void);

#endif /* APPLICATION_H_ */