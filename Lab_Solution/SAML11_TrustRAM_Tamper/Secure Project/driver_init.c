/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE != 3U))
/* Weak Non-secure callable function. Real one should be in secure gateway library. */
WEAK int32_t nsc_periph_clock_init(uint32_t gclk_id, uint32_t gclk_src)
{
	(void)gclk_id;
	(void)gclk_src;
	return 0;
}
#endif

#include <hpl_rtc_base.h>

struct timer_descriptor TIMER_0;

struct usart_sync_descriptor TARGET_IO;

struct i2c_m_sync_desc I2C_0;

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U))
	hri_mclk_set_APBAMASK_RTC_bit(MCLK);
#endif
	timer_init(&TIMER_0, RTC, _rtc_get_timer());
}

void TARGET_IO_PORT_init(void)
{

	gpio_set_pin_function(PA24, PINMUX_PA24C_SERCOM0_PAD2);

	gpio_set_pin_function(PA25, PINMUX_PA25C_SERCOM0_PAD3);
}

void TARGET_IO_CLOCK_init(void)
{
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U))
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_SERCOM0_bit(MCLK);
#else
	nsc_periph_clock_init(SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC);
	nsc_periph_clock_init(SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC);
#endif
}

void TARGET_IO_init(void)
{
	TARGET_IO_CLOCK_init();
	usart_sync_init(&TARGET_IO, SERCOM0, (void *)NULL);
	TARGET_IO_PORT_init();
}

void I2C_0_PORT_init(void)
{

	gpio_set_pin_pull_mode(PA16,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA16, PINMUX_PA16C_SERCOM1_PAD0);

	gpio_set_pin_pull_mode(PA17,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA17, PINMUX_PA17C_SERCOM1_PAD1);
}

void I2C_0_CLOCK_init(void)
{
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U))
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_SERCOM1_bit(MCLK);
#else
	nsc_periph_clock_init(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
	nsc_periph_clock_init(SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC);
#endif
}

void I2C_0_init(void)
{
	I2C_0_CLOCK_init();
	i2c_m_sync_init(&I2C_0, SERCOM1);
	I2C_0_PORT_init();
}

/**
 * \brief TRAM initialization function
 *
 * Enables TRAM peripheral, clocks and initializes driver
 */
void TRUST_RAM_0_CLOCK_init(void)
{
	hri_mclk_set_AHBMASK_TRAM_bit(MCLK);
}

void system_init(void)
{
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U))
	/* Only initialize MCU clock when the project is TrustZone secure project  */
	init_mcu();
#endif

	TIMER_0_init();

	TARGET_IO_init();

	I2C_0_init();

	TRUST_RAM_0_CLOCK_init();
	TRUST_RAM_0_init();
}
