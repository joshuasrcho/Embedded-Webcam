#include <asf.h>
#include "camera.h"
#include "wifi.h"

int main (void)
{
	sysclk_init();
	board_init();
	configure_usart_wifi();

	/* Insert application code here, after the board has been initialized. */
}
