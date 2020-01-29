/*
 * button.h
 *
 * Created: 1/28/2020 6:49:48 PM
 *  Author: ece-lab3
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <asf.h>

#define PUSH_BUTTON_ID                 ID_PIOA
#define PUSH_BUTTON_PIO                PIOA
#define PUSH_BUTTON_PIN_MSK            PIO_PA23
#define PUSH_BUTTON_ATTR               PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_EDGE

volatile uint32_t button_flag;

void configure_button(void);


#endif /* BUTTON_H_ */