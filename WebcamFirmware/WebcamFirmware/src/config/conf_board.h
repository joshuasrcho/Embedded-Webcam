/*
 * conf_board.h
 */ 

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL            (32768U)
#define BOARD_FREQ_SLCK_BYPASS          (32768U)
#define BOARD_FREQ_MAINCK_XTAL          (12000000U)
#define BOARD_FREQ_MAINCK_BYPASS        (12000000U)

/** Master clock frequency */
#define BOARD_MCK                                       CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US   15625

// Pin definitions for general board.
#define WIFI_RESET_PIN PIO_PA19_IDX
#define WIFI_CTS_PIN PIO_PA7_IDX
#define WIFI_SETUP_BUTTON_PIN PIO_PA0_IDX
#define CAM_RST_PIN PIO_PA20_IDX
#define WIFI_NETWORK_STATUS_PIN PIO_PA11_IDX


#endif // CONF_BOARD_H
