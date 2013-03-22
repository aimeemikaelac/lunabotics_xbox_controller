/*
 * controllerName.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Michael Coughlin
 */

//
// Constants for gamepad buttons
//


#include <iostream>
#include <sstream>
#include "Client.h"
#include "XBOXController.h"
#include <Windows.h>

using namespace std;


XBOXController::XBOXController(int num, int port) {
	XBOXController::port = port;
	XBOX_CONTROLLER_NUM = num;
	currentHopperSpeed = 0;
	currentLeftSide = 0;
	currentRightSide = 0;
}

bool XBOXController::IsXBOXControlConnected()
{
   //Invoke the memset(); function to zero the XBOX_CONTROLLER_State.
   memset(&XBOX_CONTROLLER_State, 0, sizeof(XINPUT_STATE));

   //We store the XInputGetState value inside result, note that result is a DWORD which is a typedef unsigned long.
   DWORD result = XInputGetState(XBOX_CONTROLLER_NUM, &XBOX_CONTROLLER_State);

   //Check if the controller is disconnected using the Ternary Operator.
   return  result == ERROR_DEVICE_NOT_CONNECTED ? false : true;
}

void XBOXController::Vibrate(float left, float right)
{
    XINPUT_VIBRATION vibration;

    //Invoke memset to zero out the XINPUT_VIBRATION.
    memset(&vibration, 0, sizeof(XINPUT_VIBRATION));

    /*
       According to MSDN Documentation on this,
       speed of the left or right motor. Valid values are
       in the range 0 to 65,535. Zero signifies no motor
       use; 65,535 signifies 100 percent motor use.
    */

    vibration.wLeftMotorSpeed = (int)left;//(int)(left*65535.0f);
    vibration.wRightMotorSpeed = (int)right;//(int)(right*65535.0f);

    //Vibrate the controller
    XInputSetState(XBOX_CONTROLLER_NUM, &vibration);
}

XINPUT_STATE XBOXController::GetState()
{
    memset(&XBOX_CONTROLLER_State, 0, sizeof(XINPUT_STATE));
    XInputGetState(XBOX_CONTROLLER_NUM, &XBOX_CONTROLLER_State);
    return XBOX_CONTROLLER_State;
}

void main()
{
   XBOXController* player0 = new XBOXController(0, 2000);

   system("color 0a"); 

    //cout << "Instructions:\n";
    //cout << "Press [A] to vibrate left only\n";
    //cout << "Press [B] to vibrate right only\n";
    //cout << "Press [BACK] to exit\n";

    while(true){ 	
        if(player0->IsXBOXControlConnected()){
        	player0->readControllerInput();

		}
		else{

			//cout << "\nERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
					//cout << "Press Any Key To Exit.";
					cin.get();
					break;
		}
        Sleep(500);

     }
}

void XBOXController::readControllerInput() {
	XINPUT_GAMEPAD gamepad = GetState().Gamepad;//player0->GetState().Gamepad;
	WORD pressed = GetState().Gamepad.wButtons;//player0->GetState().Gamepad.wButtons;
	string pressedButtons = "";

	if(pressed & XINPUT_GAMEPAD_B)
	{
		std::stringstream s;
		s<<(char)STOP_CMD;
		sendData(s.str());
	}

	if(pressed & XINPUT_GAMEPAD_BACK)
	{
		std::stringstream s;
		s<<(char)AUTO_MANUAL_TOGGLE;
		sendData(s.str());

	}

	if(pressed & XINPUT_GAMEPAD_Y) {
		std::stringstream s;
		s<<(char)RUN_HOPPER;
		currentHopperSpeed = 0;
		s<<sizeof(currentHopperSpeed);
		s<<currentHopperSpeed;
		sendData(s.str());
	}

	if(pressed & XINPUT_GAMEPAD_X) {
		std::stringstream s;
		s<<(char)STOP_HOPPER;
		sendData(s.str());
	}

	if(pressed & XINPUT_GAMEPAD_START) {
		std::stringstream s;
		s<<(char)START_CMD;
		sendData(s.str());
	}

	if(pressed & XINPUT_GAMEPAD_DPAD_DOWN) {
		currentHopperSpeed--;
		std::stringstream s;
		s<<(char)RUN_HOPPER;
		s<<sizeof(currentHopperSpeed);
		s<<currentHopperSpeed;
		sendData(s.str());
	}

	if(pressed & XINPUT_GAMEPAD_DPAD_UP) {
		currentHopperSpeed++;
		std::stringstream s;
		s<<(char)RUN_HOPPER;
		s<<sizeof(currentHopperSpeed);
		s<<currentHopperSpeed;
		sendData(s.str());
	}

	if(pressed & XINPUT_GAMEPAD_DPAD_LEFT) {
		std::stringstream s;
		s<<(char)TEST_MODE_TOGGLE;
		sendData(s.str());
	}

	if(pressed & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		std::stringstream s;
		s<<(char)RAISE_LADDER;
		sendData(s.str());
	}

	if(gamepad.bLeftTrigger>0) {
		std::stringstream s;
		s<<(char)LOWER_LADDER;
		int leftTrigger = gamepad.bLeftTrigger;
		s<<sizeof(leftTrigger);
		s<<leftTrigger;
		sendData(s.str());
	}
	if(gamepad.bRightTrigger>0) {
		std::stringstream s;
		s<<(char)RUN_LADDER;
		int rightTrigger = gamepad.bRightTrigger;
		s<<sizeof(rightTrigger);
		s<<rightTrigger;
		sendData(s.str());
	}
	//cout<<"here"<<endl;
	if(abs(gamepad.sThumbRY)-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE>0 && gamepad.sThumbRY<32768) {
		std::stringstream s;
		s<<(char)CHANGE_RIGHT;
		//sendData(s.str());
		cout<<"CHANGE_RIGHT: "<<(int)(s.str().c_str())<<endl;
		//std::stringstream s1;
		//currentRightSide = ((gamepad.sThumbRY));
		unsigned int right = gamepad.sThumbRY;
		currentRightSide = (char)(right/256);


		cout<<"Right side: "<<int(currentRightSide)<<"-------------------------------------------"<<endl;


		s<<sizeof(currentRightSide) + sizeof(currentLeftSide);
		//sendData(s1.str());
		//cout<<"Size: "<<atoi(s1.str().c_str())<<endl;
		//std::stringstream s2;
		s<<currentRightSide;
		//cout<<"Right side: "<<atoi(s2.str().c_str())<<endl;
		//sendData(s2.str());
		//std::stringstream s3;
		currentLeftSide = 0;
		s<<currentLeftSide;
		//cout<<"Left side: "<<atoi(s3.str().c_str())<<endl;
		sendData(s.str());
	}
	if(abs(gamepad.sThumbLY)-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE>0 && gamepad.sThumbLY<32768) {
		std::stringstream s;
		s<<(char)CHANGE_LEFT;
		//cout<<"left"<<endl;
		//currentLeftSide = (gamepad.sThumbLY)/128;
		int left = gamepad.sThumbLY;
		currentLeftSide = (char)(left/256);
		s<<sizeof(currentRightSide) + sizeof(currentLeftSide);
		s<<currentRightSide;
		s<<currentLeftSide;
		sendData(s.str());
	}

}


bool XBOXController::sendData(std::string message) {
	int messageLength = message.size();
	if(messageLength > 0) {
		cout<<message<<endl;
		Client client(port);
		client.sendData(message);
		return true;
	}
	else {
		return false;
	}
}


