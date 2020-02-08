/*
 * wifi.h
 */

#ifndef WIFI_H_
#define WIFI_H_

// WiFi pin definitions, WiFi UART parameters

#define BOARD_ID_USART             ID_USART0
#define BOARD_USART                USART0
#define BOARD_USART_BAUDRATE       115200
#define USART_Handler              USART0_Handler
#define USART_IRQn                 USART0_IRQn
#define ALL_INTERRUPT_MASK		   0xffffffff

// WiFi function and variable declarations

void wifi_usart_handler(void);
void process_incoming_byte_wifi(uint8_t in_byte);
void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask);
void process_data_wifi(void);
void wifi_web_setup_handler(uint32_t ul_id, uint32_t ul_mask);
void configure_usart_wifi(void);										// implemented
void configure_wifi_comm_pin(void);
void configure_wifi_web_setup_pin(void);
void write_wifi_command(char* comm, uint8_t cnt);
void write_image_to_file(void);

#endif /* WIFI_H_ */