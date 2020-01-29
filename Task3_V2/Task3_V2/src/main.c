#include <asf.h>
#include "button.h"

int main (void)
{
	sysclk_init();
	wdt_disable(WDT);
	board_init();
	
	configure_button();

	button_flag = false;

	while (1) {
		if (button_flag) {
			ioport_toggle_pin_level(PIN_LED);
			button_flag = false;
		}
	}
}
