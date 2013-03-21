/*
 * XboxController.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Michael Coughlin
 */

#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_

#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000

#include <xinput.h>
#include "UNPconstants.h"

class XBOXController {

public:
	XBOXController(int, int);
	void Vibrate(float, float);
	XINPUT_STATE GetState();
	bool IsXBOXControlConnected();
	void readControllerInput();
private:
	int port;
	char currentLeftSide;
	char currentRightSide;
	char currentHopperSpeed;
	bool sendData(std::string);
	int XBOX_CONTROLLER_NUM;
	XINPUT_STATE XBOX_CONTROLLER_State;
};


#endif /* XBOXCONTROLLER_H_ */
