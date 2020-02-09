/*
 * camera.h
 */ 


#ifndef CAMERA_H_
#define CAMERA_H_

#include <asf.h>

// Camera pin definitions, Camera TWI parameters, Camera function and variable declarations.
#define CAM_VSYNC_ID                 ID_PIOA
#define CAM_VSYNC_PIO                PIOA
#define CAM_VSYNC_PIN_MSK            PIO_PA15
#define CAM_VSYNC_ATTR               PIO_IT_RISE_EDGE

volatile uint32_t vsync_flag;

void vsync_handler(uint32_t ul_id, uint32_t ul_mask);
void init_vsync_interrupts(void);
void configure_twi(void);
void pio_capture_init(Pio *p_pio, uint32_t ul_id);
uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf, uint32_t ul_size);
void init_camera(void);
void configure_camera(void);
uint8_t start_capture(void);
uint8_t find_image_len(void);

#endif /* CAMERA_H_ */