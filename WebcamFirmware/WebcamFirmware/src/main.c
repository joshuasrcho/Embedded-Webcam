#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "camera.h"
#include "wifi.h"
//#include "timer_interface.h"

int main (void)
{
	// Initialization
	sysclk_init();
	wdt_disable(WDT);
	board_init();
	
	// Configure peripheral pins
	//configure_tc();
	configure_usart_wifi();
	configure_wifi_comm_pin();
	//char stringname[20] = "Hello\r\n";
	while (1){
		delay_ms(500);
		//write_wifi_command(stringname,1);
		usart_write_line(WIFI_USART, "Hello\r\n");
	}
	
}
