/*
 * AS5147U_Registers.hpp
 *
 *  Created on: 2025. okt. 10.
 *      Author: SNA1BP
 */

#ifndef MODULES_AS5147U_AS5147U_REGISTERS_HPP_
#define MODULES_AS5147U_AS5147U_REGISTERS_HPP_

//Volatile Memory Register Table

#define	AS5147U_NOP				0x0000	/** No operation */
#define AS5147U_ERRFL			0x0001	/** Error register */
#define AS5147U_PROG			0x0003	/** Programming register */
#define AS5147U_DIA				0x3FF5	/** DIAGNOSTIC */
#define AS5147U_AGC				0x3FF9	/** AGC Value */
#define AS5147U_SIN_DATA		0x3FFA	/** Raw digital sine channel data */
#define AS5147U_COS_DATA		0x3FFB	/** Raw digital cosine channel data */
#define AS5147U_VEL				0x3FFC	/** Velocity */
#define AS5147U_MAG				0x3FFD	/** CORDIC magnitude */
#define AS5147U_ANGLEUNC		0x3FFE	/** Measured angle without dynamic angle error compensation */
#define AS5147U_ANGLECOM		0x3FFF	/** Measured angle with dynamic angle error compensation */
#define AS5147U_ECC_Checksum	0x00D1	/** ECC checksum calculated based on actual register setting */

//Non-Volatile Register Table
#define AS5147U_DISABLE			0x0015	/** Outputs and filter disable register */
#define AS5147U_ZPOSM			0x0016	/** Zero position MSB */
#define AS5147U_ZPOSL			0x0017	/** Zero position LSB/ MAG diagnostic */
#define AS5147U_SETTINGS1		0x0018	/** Customer setting register 1 */
#define AS5147U_SETTINGS2		0x0019	/** Customer setting register 2 */
#define AS5147U_SETTINGS3		0x001A	/** Customer setting register 3*/
#define AS5147U_ECC				0x001B	/** ECC Settings*/

#endif /* MODULES_AS5147U_AS5147U_REGISTERS_HPP_ */
