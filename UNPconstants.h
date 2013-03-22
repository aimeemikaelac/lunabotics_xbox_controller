/*
 * UNP_Constants.h
 *
 *  Created on: Feb 26, 2013
 *      Author: Michael Coughlin
 */

#ifndef UNP_CONSTANTS_H_
#define UNP_CONSTANTS_H_


#define GENERAL_ERROR		0x09
#define FATAL_ERROR			0x0A
#define GENERAL_ERROR_STOP	0x0D
#define FATAL_ERROR_STOP	0x0E
#define START_CMD			0x11
#define STOP_CMD			0x12
#define CHANGE_RIGHT		0x14
#define CHANGE_LEFT			0x18
#define ROBOT_START			0x21
#define AUTO_MANUAL_TOGGLE	0x24
#define TEST_MODE_TOGGLE	0x28
#define RAISE_LADDER		0x41
#define LOWER_LADDER		0x42
#define RUN_LADDER			0x44
#define RUN_HOPPER			0x48
#define STOP_HOPPER			0x50
#define GET_MAP				0x81
#define TRANSMIT_MAP		0x82



#endif /* UNP_CONSTANTS_H_ */
