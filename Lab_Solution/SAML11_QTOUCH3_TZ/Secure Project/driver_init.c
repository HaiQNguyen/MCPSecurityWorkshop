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

struct timer_descriptor Timer;

struct usart_sync_descriptor TARGET_IO;

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void Timer_init(void)
{
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U))
	hri_mclk_set_APBAMASK_RTC_bit(MCLK);
#endif
	timer_init(&Timer, RTC, _rtc_get_timer());
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

/**
 * \brief PTC initialization function
 *
 * Enables PTC peripheral, clocks and initializes PTC driver
 */
static void PTC_clock_init(void)
{
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U))
	hri_gclk_write_PCHCTRL_reg(GCLK, PTC_GCLK_ID, CONF_GCLK_PTC_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_PTC_bit(MCLK);
#else
	nsc_periph_clock_init(PTC_GCLK_ID, CONF_GCLK_PTC_SRC);
#endif
}

void system_init(void)
{
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U))
	/* Only initialize MCU clock when the project is TrustZone secure project  */
	init_mcu();
#endif

	Timer_init();

	TARGET_IO_init();

	PTC_clock_init();
}
