#include <asf.h>
//#include "conf_board.h"
//#include "conf_clock.h"
#include "button.h"

int main (void)
{
	sysclk_init();
	wdt_disable(WDT);
	board_init();
	ioport_init();
	
	configure_button();
	
	while(1){
		if(button_flag){
			for (uint8_t ii=0;ii<10;ii++){
				ioport_toggle_pin_level(BOARD_LED);
				delay_ms(100);
			}
			button_flag = false;
		}
	}

}