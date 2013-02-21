/*
 * XboxController.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Michael Coughlin
 */

#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_
//#include "Xinput.h"
#include <xinput.h>
class XBOXController {

public:
	XBOXController(int);
	void Vibrate(float, float);
	XINPUT_STATE GetState();
	bool IsXBOXControlConnected();
private:
	int XBOX_CONTROLLER_NUM;
	XINPUT_STATE XBOX_CONTROLLER_State;
};


#endif /* XBOXCONTROLLER_H_ */
