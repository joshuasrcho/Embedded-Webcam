/*
 * camera.h
 */ 


#ifndef CAMERA_H_
#define CAMERA_H_

#include <asf.h>

// Allocating space for image
#define IMG_PRED_SIZE 100000 
uint8_t IMG_BUFFER[IMG_PRED_SIZE];
int IMG_START;
int IMG_END;
int IMG_LENGTH;	 // Number of bytes for the image data

// Camera pin definitions, Camera TWI parameters, Camera function and variable declarations.
#define IMAGE_WIDTH                    (320UL)
#define IMAGE_HEIGHT                   (240UL)

/** Camera_HSYNC pin */
#define OV_HSYNC_GPIO                  PIO_PA16_IDX
#define OV_HSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define OV_HSYNC_MASK                  PIO_PA16
#define OV_HSYNC_PIO                   PIOA
#define OV_HSYNC_ID                    ID_PIOA
#define OV_HSYNC_TYPE                  PIO_PULLUP

// Camera VSYNC pin.
#define CAM_VSYNC_GPIO                  PIO_PA15_IDX
#define CAM_VSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define CAM_VSYNC_MASK                  PIO_PA15
#define CAM_VSYNC_PIO                   PIOA
#define CAM_VSYNC_ID                    ID_PIOA
#define CAM_VSYNC_TYPE                  PIO_PULLUP

/** CAM Data Bus pins */
#define CAM_DATA_BUS_D0                 PIO_PA24_IDX
#define CAM_DATA_BUS_D1                 PIO_PA25_IDX
#define CAM_DATA_BUS_D2                 PIO_PA26_IDX
#define CAM_DATA_BUS_D3                 PIO_PA27_IDX
#define CAM_DATA_BUS_D4                 PIO_PA28_IDX
#define CAM_DATA_BUS_D5                 PIO_PA29_IDX
#define CAM_DATA_BUS_D6                 PIO_PA30_IDX
#define CAM_DATA_BUS_D7                 PIO_PA31_IDX
#define CAM_DATA_BUS_FLAGS              (PIO_INPUT | PIO_PULLUP)
#define CAM_DATA_BUS_MASK               (0xFF000000UL)
#define CAM_DATA_BUS_PIO                PIOA
#define CAM_DATA_BUS_ID                 ID_PIOA
#define CAM_DATA_BUS_TYPE               PIO_INPUT
#define CAM_DATA_BUS_ATTR               PIO_DEFAULT

/** OV_RST pin definition */
#define CAM_RST_GPIO                    PIO_PA20_IDX
#define CAM_RST_FLAGS                   (PIO_OUTPUT_1 | PIO_DEFAULT)
#define CAM_RST_MASK                    PIO_PA20
#define CAM_RST_PIO                     PIOA
#define CAM_RST_ID                      ID_PIOA
#define CAM_RST_TYPE                    PIO_OUTPUT_1

/** PCK1 */
#define PIN_PCK1                       (PIO_PA17_IDX)
#define PIN_PCK1_FLAGS                 (PIO_PERIPH_B | PIO_DEFAULT)              

/** TWI0 data pin */
#define PIN_TWI_TWD0                   {PIO_PA3A_TWD0, PIOA, ID_PIOA, \
										PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 clock pin */
#define PIN_TWI_TWCK0                  {PIO_PA4A_TWCK0, PIOA, ID_PIOA,	\
										PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 Data pins definition */
#define TWI0_DATA_GPIO                 PIO_PA3_IDX
#define TWI0_DATA_FLAGS                (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_DATA_MASK                 PIO_PA3
#define TWI0_DATA_PIO                  PIOA
#define TWI0_DATA_ID                   ID_PIOA
#define TWI0_DATA_TYPE                 PIO_PERIPH_A
#define TWI0_DATA_ATTR                 PIO_DEFAULT

/** TWI0 clock pins definition */
#define TWI0_CLK_GPIO                  PIO_PA4_IDX
#define TWI0_CLK_FLAGS                 (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_CLK_MASK                  PIO_PA4
#define TWI0_CLK_PIO                   PIOA
#define TWI0_CLK_ID                    ID_PIOA
#define TWI0_CLK_TYPE                  PIO_PERIPH_A
#define TWI0_CLK_ATTR                  PIO_DEFAULT

/** TWI0 pins */
#define PINS_TWI0                      PIN_TWI_TWD0, PIN_TWI_TWCK0
#define ID_BOARD_TWI		               ID_TWI0
#define BOARD_TWI			                 TWI0
#define BOARD_TWI_IRQn		             TWI0_IRQn

/* TWI clock frequency in Hz (400KHz) */
#define TWI_CLK     (400000UL)

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