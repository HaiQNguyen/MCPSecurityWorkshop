/**
 * \file
 *
 * \brief TrustZone secure gateway veneer header file.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef _TRUSTZONE_VENEER_H_INCLUDED
#define _TRUSTZONE_VENEER_H_INCLUDED

#include <compiler.h>

/* ======== Non-secure callable common driver functions ======== */

/**
 *  \brief External IRQ settings for EIC
 */
//@{
struct ext_irq_setting {
	uint32_t evctrl;    /** EIC.EVCTRL register value */
	uint32_t config[1]; /** EIC.CONFIG register value */
	uint32_t asynch;    /** EIC.ASYNCH register value */
	uint32_t debouncen; /** EIC.DEBOUNCEN register value */
};
//@}

/**
 * \brief Initialize peripheral clock.
 *
 * \param[in] gclk_id    GCLK ID for the peripheral
 * \param[in] gclk_src   GCLK source for the peripheral
 *
 * \return The status of operation request
 * \retval  0 The operation is completed successfully
 * \retval  1 No operation needed, the peripheral clock is enabled already
 */
extern int32_t nsc_periph_clock_init(uint32_t gclk_id, uint32_t gclk_src);

/**
 * \brief Initialize non-secure external interrupt.
 *
 * \param[in] irq_setting    Non-secure external IRQ settings
 *
 * \return 0 if the operation is completed successfully
 */
extern int32_t nsc_ext_irq_init(struct ext_irq_setting irq_setting);

/* ======== Non-secure callable functions defined by customer ======== */

/* Add your function declaration here */

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
extern void nonsecure_ConsolePuts (uint8_t * string);

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
extern void nonsecure_PrintBytes(uint8_t * ptr, uint8_t length);

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
extern void nonsecure_GetRevSerialNumber(uint8_t *serial_buff, uint8_t serial_size, uint8_t * rev_buff, uint8_t rev_size);

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
extern void nonsecure_ReadWholeRAM(uint8_t *buff, uint8_t size);
#endif /* _TRUSTZONE_VENEER_H_INCLUDED */
