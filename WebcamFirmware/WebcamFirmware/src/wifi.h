/*
 * wifi.h
 */

#ifndef WIFI_H_
#define WIFI_H_

# include <asf.h>
# include <string.h>

// WiFi pin definitions, WiFi UART parameters

#define WIFI_ID_USART             ID_USART0
#define WIFI_USART                USART0
#define WIFI_USART_BAUDRATE       115200
#define wifi_usart_handler        USART0_Handler
#define USART_IRQn                 USART0_IRQn
#define ALL_INTERRUPT_MASK		   0xffffffff
/** USART0 pin RX */
#define PIN_USART0_RXD    {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin TX */
#define PIN_USART0_TXD    {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin CTS */
#define PIN_USART0_CTS    {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin RTS */
#define PIN_USART0_RTS    {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX        (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

#define WIFI_COMM_ID                 ID_PIOA
#define WIFI_COMM_PIO                PIOA
#define WIFI_COMM_PIN_MSK            PIO_PA12
#define WIFI_COMM_ATTR               PIO_IT_RISE_EDGE

#define WIFI_SETUP_ID                 ID_PIOA
#define WIFI_SETUP_PIO                PIOA
#define WIFI_SETUP_PIN_MSK            PIO_PA2
#define WIFI_SETUP_ATTR               PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE



// WiFi function and variable declarations

void process_incoming_byte_wifi(uint8_t in_byte);
void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask);
void process_data_wifi(void);
void wifi_web_setup_handler(uint32_t ul_id, uint32_t ul_mask);
void configure_usart_wifi(void);										// implemented
void configure_wifi_comm_pin(void);
void configure_wifi_web_setup_pin(void);
void write_wifi_command(char* comm, uint8_t cnt);
void write_image_to_file(void);

volatile char input_line_wifi[1000];
volatile uint32_t received_byte_wifi;
volatile uint32_t wifi_web_setup_flag;
volatile unsigned int input_pos_wifi;
volatile uint32_t Ready2TransferFlag;
volatile uint32_t StreamOpen;

#endif /* WIFI_H_ */