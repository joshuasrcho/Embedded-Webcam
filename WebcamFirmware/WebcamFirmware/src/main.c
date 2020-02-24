#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "camera.h"
#include "wifi.h"
#include "timer_interface.h"

int main (void)
{
	// Initialization
	sysclk_init();
	wdt_disable(WDT);
	board_init();
	init_camera();
	
	// Configure peripheral pins, Initialize WiFi and camera modules
	configure_camera();
	configure_tc();
	configure_usart_wifi();
	configure_wifi_comm_pin();
	configure_wifi_web_setup_pin();
	
	
	
	// Reset wifi module
	ioport_set_pin_level(WIFI_RESET_PIN, false);
	delay_ms(100);
	ioport_set_pin_level(WIFI_RESET_PIN, true);
	
	// Tell the WiFi to turn off the command prompt and command  echo
	write_wifi_command("set sy c p off\r\n",2);
	write_wifi_command("set sy c e off\r\n",2);
	
	while (1){
		if (wifi_web_setup_flag){
			wifi_web_setup_flag = 0;
			write_wifi_command("setup web\r\n",3);
			} // wait for wifi web setup flag high
		 
	}
	
}
