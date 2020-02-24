/*
 * camera.c
 */ 

#include "camera.h"
#include "ov2640.h"

volatile uint32_t vsync_flag = false;

/* Pointer to the image data destination buffer */
uint8_t *cap_dest_buf;

uint16_t cap_line = (IMAGE_WIDTH * 2);
uint16_t cap_rows = IMAGE_HEIGHT;

void vsync_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);
	
	vsync_flag = true;
}

void init_vsync_interrupts(void)
{
	/* Configure PIO clock. */
	pmc_enable_periph_clk(CAM_VSYNC_ID);

	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(CAM_VSYNC_PIO, CAM_VSYNC_ID, CAM_VSYNC_MASK,
			CAM_VSYNC_TYPE, vsync_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)CAM_VSYNC_ID);

	/* Enable PIO interrupt lines. */
	pio_enable_interrupt(CAM_VSYNC_PIO, CAM_VSYNC_MASK);
}



void pio_capture_init(Pio *p_pio, uint32_t ul_id)
{
	/* Enable periphral clock */
	pmc_enable_periph_clk(ul_id);

	/* Disable pio capture */
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_PCEN);

	/* Disable rxbuff interrupt */
	p_pio->PIO_PCIDR |= PIO_PCIDR_RXBUFF;

	/* 32bit width*/
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_DSIZE_Msk);
	p_pio->PIO_PCMR |= PIO_PCMR_DSIZE_WORD;

	/* Only HSYNC and VSYNC enabled */
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_ALWYS);
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_HALFS);

	#if !defined(DEFAULT_MODE_COLORED)
	/* Samples only data with even index */
	p_pio->PIO_PCMR |= PIO_PCMR_HALFS;
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_FRSTS);
	#endif
}

uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf,
uint32_t ul_size)
{
	/* Check if the first PDC bank is free */
	if ((p_pio->PIO_RCR == 0) && (p_pio->PIO_RNCR == 0)) {
		p_pio->PIO_RPR = (uint32_t)uc_buf;
		p_pio->PIO_RCR = ul_size;
		p_pio->PIO_PTCR = PIO_PTCR_RXTEN;
		return 1;
		} else if (p_pio->PIO_RNCR == 0) {
		p_pio->PIO_RNPR = (uint32_t)uc_buf;
		p_pio->PIO_RNCR = ul_size;
		return 1;
		} else {
		return 0;
	}
}

void init_camera(void)
{

	/* Init Vsync handler*/
	init_vsync_interrupts();

	/* Init PIO capture*/
	pio_capture_init(CAM_DATA_BUS_PIO, CAM_DATA_BUS_ID);


	/* Init PCK0 to work at 24 Mhz */
	/* 96/4=24 Mhz */
	PMC->PMC_PCK[0] = (PMC_PCK_PRES_CLK_4 | PMC_PCK_CSS_PLLA_CLK);
	PMC->PMC_SCER = PMC_SCER_PCK0;
	while (!(PMC->PMC_SCSR & PMC_SCSR_PCK0)) {
	}

	configure_twi();

}

void configure_twi(void){
	twi_options_t opt;
	
	gpio_configure_pin(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
	gpio_configure_pin(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
		
		/* Enable TWI peripheral */
		pmc_enable_periph_clk(ID_BOARD_TWI);

		/* Init TWI peripheral */
		opt.master_clk = sysclk_get_cpu_hz();
		opt.speed      = TWI_CLK;
		twi_master_init(BOARD_TWI, &opt);

		/* Configure TWI interrupts */
		NVIC_DisableIRQ(BOARD_TWI_IRQn);
		NVIC_ClearPendingIRQ(BOARD_TWI_IRQn);
		NVIC_SetPriority(BOARD_TWI_IRQn, 0);
		NVIC_EnableIRQ(BOARD_TWI_IRQn);
}

void configure_camera(void){
	/* ov7740 Initialization */
	while (ov_init(BOARD_TWI) == 1) {
	}

	/* ov7740 configuration */
	ov_configure(BOARD_TWI, QVGA_YUV422_20FPS);

	/* Wait 3 seconds to let the image sensor to adapt to environment */
	delay_ms(3000);
}


uint8_t start_capture(void)
{
	/* Set capturing destination address*/
	cap_dest_buf = (uint8_t *)CAP_DEST;

	/* Set cap_rows value*/
	cap_rows = IMAGE_HEIGHT;

	/* Enable vsync interrupt*/
	pio_enable_interrupt(CAM_VSYNC_PIO, CAM_VSYNC_MASK);

	/* Capture acquisition will start on rising edge of Vsync signal.
	 * So wait g_vsync_flag = 1 before start process
	 */
	while (!vsync_flag) {
	}

	/* Disable vsync interrupt*/
	pio_disable_interrupt(CAM_VSYNC_PIO, CAM_VSYNC_MASK);

	/* Enable pio capture*/
	pio_capture_enable(CAM_DATA_BUS_PIO);

	/* Capture data and send it to external SRAM memory thanks to PDC
	 * feature */
	pio_capture_to_buffer(CAM_DATA_BUS_PIO, cap_dest_buf,
			(cap_line * cap_rows) >> 2);

	/* Wait end of capture*/
	while (!((CAM_DATA_BUS_PIO->PIO_PCISR & PIO_PCIMR_RXBUFF) ==
			PIO_PCIMR_RXBUFF)) {
	}

	/* Disable pio capture*/
	pio_capture_disable(CAM_DATA_BUS_PIO);

	/* Reset vsync flag*/
	vsync_flag = false;
}

uint8_t find_image_len(void){
	return 0;
}