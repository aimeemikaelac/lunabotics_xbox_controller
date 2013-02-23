/*
 * controllerName.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Michael Coughlin
 */

//
// Constants for gamepad buttons
//
#include <Windows.h>
#include "XBOXController.h"
#include <iostream>


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

using namespace std;


XBOXController::XBOXController(int num) {
	XBOX_CONTROLLER_NUM = num;
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
   XBOXController* player1 = new XBOXController(0); 

   system("color 0a"); 

    cout << "Instructions:\n";
    cout << "Press [A] to vibrate left only\n";
    cout << "Press [B] to vibrate right only\n";
    cout << "Press [BACK] to exit\n";          

    while(true){ 	
        if(player1->IsXBOXControlConnected()){
        	XINPUT_GAMEPAD gamepad = player1->GetState().Gamepad;
        	WORD pressed = player1->GetState().Gamepad.wButtons;
			if(pressed & XINPUT_GAMEPAD_A)
			{  
				cout << " A ";
//				player1->Vibrate(65535, 0);
			}
			if(pressed & XINPUT_GAMEPAD_B)
			{ 
				cout << " B ";
//				player1->Vibrate(0, 65535);
			}

			if(pressed & XINPUT_GAMEPAD_BACK)
			{
				cout<<" BACK  ";
//				break;

			}
			if(pressed & XINPUT_GAMEPAD_Y) {
				cout<<" Y ";
			}
			if(pressed & XINPUT_GAMEPAD_X) {
				cout<<" X  ";
			}
			if(pressed & XINPUT_GAMEPAD_START) {
				cout<<" START ";
			}
			if(pressed & XINPUT_GAMEPAD_DPAD_DOWN) {
				cout<<" DPAD_DOWN ";
			}
			if(pressed & XINPUT_GAMEPAD_DPAD_UP) {
				cout<<" DPAD_UP ";
			}
			if(pressed & XINPUT_GAMEPAD_DPAD_LEFT) {
				cout<<" DPAD_LEFT ";
			}
			if(pressed & XINPUT_GAMEPAD_DPAD_RIGHT) {
				cout<<" DPAD_RIGHT ";
			}
			if(pressed & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				cout<<" LEFT_SHOULDER ";
			}
			if(pressed & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				cout<<" RIGHT_SHOULDER ";
			}
			cout<<endl;
//			if(pressed & XINPUT_GAMEPAD_) {
//				cout<<"X";
//			}
			if(gamepad.bLeftTrigger>0) {
				cout<<"LEFT_TRIGGER: ";
				cout<<(unsigned int)(player1->GetState().Gamepad.bLeftTrigger)<<endl;
			}
			if(gamepad.bRightTrigger>0) {
				cout<<"RIGHT_TRIGGER: ";
				cout<<(unsigned int)(player1->GetState().Gamepad.bRightTrigger)<<endl;
			}
			if(abs(gamepad.sThumbLY)-XINPUT_GAMEPAD_TRIGGER_THRESHOLD>0) {
				cout<<"LEFT_THUMB_Y: ";
				cout<<(unsigned int)(player1->GetState().Gamepad.sThumbLY)<<endl;
			}
			if(abs(gamepad.sThumbRY)-XINPUT_GAMEPAD_TRIGGER_THRESHOLD>0) {
				cout<<"RIGHT_THUMB_Y: ";
				cout<<(unsigned int)(player1->GetState().Gamepad.sThumbRY)<<endl;
			}
		}
		else{

			cout << "\nERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
					cout << "Press Any Key To Exit.";
					cin.get();
					break;
		}

	 
     }
	//delete player1;
}
