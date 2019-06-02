/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static struct timer_task TIMER_0_task1, TIMER_0_task2;
/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

/**
 * Example of using TARGET_IO to write "Hello World" using the IO abstraction.
 */
void TARGET_IO_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&TARGET_IO, &io);
	usart_sync_enable(&TARGET_IO);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void I2C_0_example(void)
{
	struct io_descriptor *I2C_0_io;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x12, I2C_M_SEVEN);
	io_write(I2C_0_io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using TRUST_RAM_0 to read and write security RAM.
 */
void TRUST_RAM_0_example(void)
{
	uint32_t i;
	uint32_t tram_src_data[3] = {0x12345678, 0xAABBCCDD, 0x55AAABCD};
	uint32_t tram_chk_data[3];

	/* Write data to TRAM */
	for (i = 0; i < 3; i++) {
		TRUST_RAM_0_write(i, tram_src_data[i]);
	}

	/* Read data from TRAM */
	for (i = 0; i < 3; i++) {
		tram_chk_data[i] = TRUST_RAM_0_read(i);
	}

	/* Check data */
	for (i = 0; i < 3; i++) {
		if (tram_src_data[i] != tram_chk_data[i]) {
			while (1)
				; /* Error happen */
		}
	}
}
