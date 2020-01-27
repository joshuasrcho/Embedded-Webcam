/*
 * button.h
 *
 * Created: 1/27/2020 1:20:33 PM
 *  Author: joshuasrcho
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <asf.h>

//#define BOARD_BUTTON PIO_PB3_IDX

#define PUSH_BUTTON_ID                 ID_PIOA
#define PUSH_BUTTON_PIO                PIOA
#define PUSH_BUTTON_PIN_MSK            PIO_PA23
#define PUSH_BUTTON_ATTR               PIO_PULLUP | PIO_DEBOUNCE |PIO_IT_RISE_EDGE

volatile uint32_t button_flag;
void configure_button(void);


#endif /* BUTTON_H_ */