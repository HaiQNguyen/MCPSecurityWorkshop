
/** @file Secure_Funcion.c
 *  @brief Implement the secure functions.  
 *
 *	Some of the functions will be share with the non-secure application
 *	through veneer table
 *
 *  @author Quang Hai Nguyen
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */

#include "Secure_Functions.h"
#include "sam.h"

void sc_RTC_Init(void)
{
	/* Configure PA08 as RTC IN0 (peripheral I) */
	PORT_SEC->Group[0].WRCONFIG.reg = (uint32_t)(PORT_WRCONFIG_WRPINCFG|PORT_WRCONFIG_WRPMUX|PORT_WRCONFIG_PINMASK(1<<8)|PORT_WRCONFIG_PMUXEN|PORT_WRCONFIG_PMUX(8));
	
	/* Set APB Clock */
	MCLK->APBAMASK.reg |= MCLK_APBAMASK_RTC;
	
	/* Select RTC clock on XOSC32K */
	OSC32KCTRL->RTCCTRL.reg = OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K;
	
	/* Reset RTC */
	RTC->MODE0.CTRLA.reg = RTC_MODE0_CTRLA_SWRST;
	while(RTC->MODE0.SYNCBUSY.bit.SWRST);
	
	RTC->MODE0.CTRLA.reg = (RTC_MODE0_CTRLA_MODE_COUNT32 | RTC_MODE0_CTRLA_PRESCALER_DIV1 | RTC_MODE0_CTRLA_COUNTSYNC);
	
	/*Configure RTC Tamper on IN0 */
	RTC->MODE0.TAMPCTRL.reg = ( RTC_TAMPCTRL_IN0ACT_WAKE | 	// Tamper action : Wake and set Tamper flag
	RTC_TAMPCTRL_TAMLVL0 |		// Tamper edge : rising
	RTC_TAMPCTRL_DEBNC0	 		// Tamper Debounce  :Detect edge with synchronous stability
	);
	
	/* Enable Tamper event output*/
	RTC->MODE0.EVCTRL.reg = (RTC_MODE0_EVCTRL_TAMPEREO | RTC_MODE0_EVCTRL_OVFEO);
	
	/* Enable RTC */
	RTC->MODE0.CTRLA.reg |= RTC_MODE0_CTRLA_ENABLE;
	while(RTC->MODE0.SYNCBUSY.bit.ENABLE);
}

void sc_TRAM_Init(void)
{
	/* Enable TRAM in Tamper mode */
	TRAM->CTRLA.reg = TRAM_CTRLA_SWRST;
	while (TRAM->SYNCBUSY.bit.SWRST);
	/* Enable Data Scrambling with internal key */
	TRAM->DSCC.reg = (TRAM_DSCC_DSCEN |TRAM_DSCC_DSCKEY(0xCAFE));
	/* Enable TRAM security features (TAMPER , data remanence prevention , silent access*/
	TRAM->CTRLA.reg = (TRAM_CTRLA_TAMPERS|TRAM_CTRLA_SILACC|TRAM_CTRLA_DRP);
	TRAM->CTRLA.reg |= TRAM_CTRLA_ENABLE ;
}

void sc_TRAM_Write(uint8_t * data, uint8_t size, uint8_t offset)
{
	uint8_t i;
	uint8_t *addr_b;
	addr_b = (uint8_t*)&TRAM->RAM[0].reg;
	
	/*return if data bigger than RAM size*/
	if(size > 128)
		return;
	
	/* Initialize TRAM content */
	for (i=0; i < size ; i++) {
		*(addr_b + offset + i) = data[i];
	}
	
}

void sc_TRAM_Read(uint8_t * data, uint8_t size, uint8_t offset)
{
	int i;
	uint8_t *addr_b;
	addr_b = (uint8_t*)&TRAM->RAM[0].reg;
	
	/*Stop operation if size bigger than TRAM size*/
	if(size + offset > 128)
		return;
	
	for (i=0; i < size; i++)
	{
		data[i] = *(addr_b + offset + i);
	}
}

void sc_ReadWholeRAM(u_int8_t *buff, uint8_t size)
{
	if(size != 128)
		return;
		
	sc_TRAM_Read(buff, 128, 0);
}

void sc_ConsolePuts (uint8_t * string)
{
	/* Set display foreground color to green */
	printf("\033[0;32m");
	/* Print string on console */
	printf("%s", string);
}

void nsc_ConsolePuts (uint8_t * string)
{
	/* Set display foreground color to red */
	printf("\033[0;31m");
	/* Print string on console */
	printf("%s", string);
}

void nsc_PrintBytes(uint8_t * ptr, uint8_t length)
{
	uint8_t i = 0;
	uint8_t line_count = 0;
	
	/* Set display foreground color to red */
	printf("\033[0;31m");
	
	for(;i < length; i++) {
		printf("0x%02x, ",ptr[i]);
		line_count++;
		if(line_count == 8) {
			printf("\r\n");
			line_count = 0;
		}
	}
		
	printf("\r\n");
}

void nsc_GetRevSerialNumber(uint8_t *serial_buff, uint8_t serial_size, uint8_t * rev_buff, uint8_t rev_size)
{
	/*Make sure to have correct size*/
	if(serial_size != 9 || rev_size != 4)
		return;
		
	sc_TRAM_Read(serial_buff, serial_size, 0x00 );
	sc_TRAM_Read(rev_buff, rev_size, 0x00 + serial_size );

}