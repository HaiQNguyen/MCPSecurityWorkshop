
/** @file main.c
 *  @brief main file for the secure application
 *
 *  This file content the initialization code for the secure application
 *	and non-secure application. NOTE RTC and tamper pin PA08 will be initialized 
 *	manually because they are not correctly supported by Atmel START
 *
 *	@author Quang Hai Nguyen
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */


#include <atmel_start.h>
#include "Secure_functions/Secure_Functions.h"
#include "cryptoauthlib.h"
#include "atca_host.h"



/* Define section -----------------------------------------------------------------------*/

/* TZ_START_NS: Start address of non-secure application */
#define TZ_START_NS			0x00008000
#define DATA_OFFSET_IN_RAM	0x00
#define REVISION_SIZE		0x04
#define TRUST_RAM_SIZE		128

/* Handle the response status from the secure element*/
#define CHECK_STATUS(s)										\
if(s != ATCA_SUCCESS) {										\
	printf("status code: 0x%x\r\n", s);						\
	printf("Error: Line %d in %s\r\n", __LINE__, __FILE__); \
	while(1);												\
}


/* Local variable section -----------------------------------------------------------------*/

/* typedef for non-secure callback functions */
typedef void (*ns_funcptr_void) (void) __attribute__((cmse_nonsecure_call));

/**	
 *	@brief data structure for secure element instant
 *	
 *	It contains the information to initialize the communication between controller and secure element
 */
ATCAIfaceCfg cfg_ateccx08a_i2c_host = {
	.iface_type				= ATCA_I2C_IFACE,
	.devtype				= ATECC608A,
	.atcai2c.slave_address	= 0xC0,
	.atcai2c.bus			= 1,
	.atcai2c.baud			= 400000,
	.wake_delay				= 800,
	.rx_retries				= 20,
	.cfg_data              = &I2C_0
};

/* Local function prototype section --------------------------------------------------------*/

/**
 *  @brief Print a bytes on the console terminal
 *
 *	@param	ptr		pointer to byte array to print
 *	@param	size	number of byte to print	
 *	
 *	@return	NULL	always return
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
static void print_bytes(uint8_t * ptr, uint8_t length);

int main(void)
{
	
	volatile ATCA_STATUS status;
	uint8_t serial_number[ATCA_SERIAL_NUM_SIZE];
	uint8_t revision_number[REVISION_SIZE];
	uint8_t ram_buff[TRUST_RAM_SIZE];
	
	/* Pointer to Non secure reset handler definition*/
	ns_funcptr_void NonSecure_ResetHandler;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	sc_ConsolePuts((uint8_t *)"hello world from secure application\r\n");
	
	/*Initial TrustRAM and display its content*/
	sc_RTC_Init();
	sc_TRAM_Init();
	sc_ReadWholeRAM(ram_buff, TRUST_RAM_SIZE);
	print_bytes(ram_buff,TRUST_RAM_SIZE);
	
	/*Intial ATECC508, read out revision number, serial number and write them to TrustRAM*/
	status = atcab_init( &cfg_ateccx08a_i2c_host );
	CHECK_STATUS(status);
	
	sc_ConsolePuts((uint8_t *)"Initializing ATECC508\r\n");
	
	status = atcab_read_serial_number((uint8_t*)&serial_number);
	CHECK_STATUS(status);
	status = atcab_info(revision_number);
	CHECK_STATUS(status);
	
	sc_TRAM_Write(serial_number, ATCA_SERIAL_NUM_SIZE, DATA_OFFSET_IN_RAM);
	sc_TRAM_Write(revision_number, REVISION_SIZE, DATA_OFFSET_IN_RAM + ATCA_SERIAL_NUM_SIZE);
	
	sc_ConsolePuts((uint8_t *)"ATECC508 is initialized. Revision and serial number are stored in Trust Ram\r\n");
	
	/* Set non-secure main stack (MSP_NS) */
	__TZ_set_MSP_NS(*((uint32_t *)(TZ_START_NS)));
	
	/* Get non-secure reset handler */
	NonSecure_ResetHandler = (ns_funcptr_void)(*((uint32_t *)((TZ_START_NS) + 4U)));
	
	/* Start Non-secure Application */
	NonSecure_ResetHandler();
	
	
	/* Replace with your application code */
	while (1) {
		
		
	}
}

static void print_bytes(uint8_t * ptr, uint8_t length)
{
	
	uint8_t i = 0;
	uint8_t line_count = 0;
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
