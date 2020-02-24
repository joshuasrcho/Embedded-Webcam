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
	
	/* Configure TWI pins */
	#ifdef CONF_BOARD_TWI0		
		gpio_configure_pin(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
		gpio_configure_pin(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
	#endif
		
		/* Configure Image sensor pins */
	#ifdef CONF_BOARD_OV2640_IMAGE_SENSOR
		/*gpio_configure_pin(OV_SW_OVT_GPIO, OV_SW_OVT_FLAGS);
		gpio_configure_pin(OV_RST_GPIO, OV_RST_FLAGS);
		gpio_configure_pin(OV_FSIN_GPIO, OV_FSIN_FLAGS);
		gpio_configure_pin(OV_HSYNC_GPIO, OV_HSYNC_FLAGS);*/
		gpio_configure_pin(CAM_VSYNC_GPIO, CAM_VSYNC_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D0, CAM_DATA_BUS_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D1, CAM_DATA_BUS_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D2, CAM_DATA_BUS_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D3, CAM_DATA_BUS_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D4, CAM_DATA_BUS_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D5, CAM_DATA_BUS_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D6, CAM_DATA_BUS_FLAGS);
		gpio_configure_pin(CAM_DATA_BUS_D7, CAM_DATA_BUS_FLAGS);
	#endif	
	
	/* Configure PCK0 pins */
	#ifdef CONF_BOARD_PCK1
		gpio_configure_pin(PIN_PCK1, PIN_PCK1_FLAGS);
	#endif

}
