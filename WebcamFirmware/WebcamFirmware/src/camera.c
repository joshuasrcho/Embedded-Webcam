/*
 * camera.c
 */ 

#include "camera.h"

volatile uint32_t vsync_flag = false;

void vsync_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);
	
	vsync_flag = true;
}

void init_vsync_interrupts(void)
{
	/* Configure PIO clock. */
	pmc_enable_periph_clk(CAM_VSYNC_ID);

	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(CAM_VSYNC_PIO, CAM_VSYNC_ID, CAM_VSYNC_PIN_MSK,
			CAM_VSYNC_ATTR, wifi_command_response_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)CAM_VSYNC_ID);

	/* Enable PIO interrupt lines. */
	pio_enable_interrupt(CAM_VSYNC_PIO, CAM_VSYNC_PIN_MSK);
}