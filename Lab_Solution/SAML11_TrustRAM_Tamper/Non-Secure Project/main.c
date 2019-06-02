
/* Include section-----------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include "trustzone_veneer.h"

/* Define section------------------------------------------------------------------------------------*/
#define SERIAL_NUM_SIZE		0x09
#define REVISION_SIZE		0x04
#define TRUST_RAM_SIZE		128


int main(void)
{
	uint8_t rev[REVISION_SIZE];
	uint8_t ser[SERIAL_NUM_SIZE];
	uint8_t ram_buff[TRUST_RAM_SIZE];
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	nonsecure_ConsolePuts((uint8_t *)"Hello World from non secure application\r\n");
	
	
	/* Replace with your application code */
	while (1) {
		
		/*Waiting for user input to read the data from Trust RAM*/
		nonsecure_ConsolePuts((uint8_t *)"\r\n\r\n");
		nonsecure_ConsolePuts((uint8_t *)"Press SW0 to call and print serial number and revision\r\n");
		while(gpio_get_pin_level(SW0));
		
		/* Read data from Trust RAM and print on Terminal*/
		nonsecure_ReadWholeRAM(ram_buff, TRUST_RAM_SIZE);
		nonsecure_ConsolePuts((uint8_t *)"Data in RAM after initialization\r\n");
		nonsecure_PrintBytes(ram_buff, TRUST_RAM_SIZE);
		
		nonsecure_GetRevSerialNumber(ser, SERIAL_NUM_SIZE, rev, REVISION_SIZE);
		
		nonsecure_ConsolePuts((uint8_t *)"Serial number: \r\n");
		nonsecure_PrintBytes(ser, SERIAL_NUM_SIZE);
		nonsecure_ConsolePuts((uint8_t *)"Revision number: \r\n");
		nonsecure_PrintBytes(rev, REVISION_SIZE);
		
		delay_ms(500);
	}
}
