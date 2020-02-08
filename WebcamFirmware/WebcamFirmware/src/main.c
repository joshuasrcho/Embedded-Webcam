#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "camera.h"
#include "wifi.h"

int main (void)
{
	sysclk_init();
	wdt_disable(WDT);
	board_init();
	
	configure_usart_wifi();
	configure_wifi_comm_pin();
	
	while (1){
		delay_ms(500);
		usart_write_line(WIFI_USART, "Hello\r\n");
	}
	
}
