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
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	ioport_init();
	
	ioport_set_pin_dir(WIFI_RESET_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(WIFI_RESET_PIN, true);
	
	ioport_set_pin_dir(WIFI_SETUP_BUTTON_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(WIFI_SETUP_BUTTON_PIN, IOPORT_MODE_PULLUP);
	
	ioport_set_pin_dir(WIFI_CTS_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(WIFI_CTS_PIN, false);
	
	//Pull RST pin of Camera high
	ioport_set_pin_dir(CAM_RST_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(CAM_RST_PIN, true);
	
	ioport_set_pin_dir(WIFI_NETWORK_STATUS_PIN, IOPORT_DIR_INPUT);

}
