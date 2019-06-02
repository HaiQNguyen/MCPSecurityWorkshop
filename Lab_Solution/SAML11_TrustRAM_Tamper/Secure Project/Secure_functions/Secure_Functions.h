
/** @file Secure_Funcion.h
 *  @brief Header file of Secure_Function.c  
 *
 *	Contain global functions and variables to be called 
 *
 *  @author Quang Hai Nguyen
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */

#include <atmel_start.h>

#ifndef SECURE_FUNCTIONS_H_
#define SECURE_FUNCTIONS_H_

/**
 *  @brief Initialize the RTC	
 *	
 *	@return	NULL	always return
 *
 *	It is including the tamper detection setup
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void sc_RTC_Init(void);

/**
 *  @brief Write data to the Trust RAM
 *
 *	@param	data	pointer to byte array written to RAM
 *	@param	size	number of byte written
 *	@param	offset	where to write data in RAM, starting from 0x00
 *	
 *	@return	NULL	always return
 *
 *	Maximum 128 bytes can be written into RAM since we are using silent mode
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void sc_TRAM_Write(uint8_t * data, uint8_t size, uint8_t offset);

/**
 *  @brief Read Data from Trust RAM
 *
 *	@param	ptr		buffer to store data read from RAM
 *	@param	size	number of byte to read
 *	@param	offset	where to read byte, starting from 0x00	
 *	
 *	@return	NULL	always return
 *
 *	Maximum 128 bytes can be read from RAM since it is running silent mode
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void sc_TRAM_Read(uint8_t * data, uint8_t size, uint8_t offset);

/**
 *  @brief Init  Trust RAM
 *
 *	@return	NULL	always return
 *
 *	the initialization includes silent mode, tamper detection
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void sc_TRAM_Init(void);

/**
 *  @brief Print text in secure mode
 *
 *	@param	string	Text to be printed	
 *	
 *	@return	NULL	always return
 *
 *	Text in secure mode will be printed in green
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void sc_ConsolePuts (uint8_t * string);

/**
 *  @brief Print text in non secure mode
 *
 *	@param	string	Text to be printed	
 *	
 *	@return	NULL	always return
 *
 *	Text in non secure mode will be printed in red
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void nsc_ConsolePuts (uint8_t * string);

/**
 *  @brief Print a bytes on the console terminal in non secure mode
 *
 *	@param	ptr		pointer to byte array to print
 *	@param	length	number of byte to print	
 *	
 *	@return	NULL	always return
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void nsc_PrintBytes(uint8_t * ptr, uint8_t length);

/**
 *  @brief Get serial number and revision from Trust RAM
 *
 *	@param	serial_buff		buffer storing serial number
 *	@param	serial_size		size of serial number
 *	@param	rev_buff		buffer storing revision
 *	@param	rev_size		size of revision
 *	
 *	@return	NULL	always return
 *
 *	This function allows non-secure application to read out the serial number\n
 *	and revision from Trust RAM
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */ 
void nsc_GetRevSerialNumber(uint8_t *serial_buff, uint8_t serial_size, uint8_t * rev_buff, uint8_t rev_size); 

/**
 *  @brief	Read out complete data in Trust RAM
 *
 *	@param	ptr		buffer storing data from RAM
 *	@param	size	size of RAM (128 bytes)
 *	
 *	@return	NULL	always return
 *
 *	It allows non-secure application accesses the data in trust RAM
 *	
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void sc_ReadWholeRAM(u_int8_t *buff, uint8_t size);

#endif /* SECURE_FUNCTIONS_H_ */