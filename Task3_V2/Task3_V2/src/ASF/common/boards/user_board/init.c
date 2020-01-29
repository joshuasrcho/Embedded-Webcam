/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	ioport_init();
	
	ioport_set_pin_dir(PIN_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_LED, false);
	
	ioport_set_pin_dir(PIN_BUTTON, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PIN_BUTTON, IOPORT_MODE_PULLUP);
}
