/*
 * Client.h
 *
 *  Created on: Feb 23, 2013
 *      Author: Michael Coughlin
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include "socket.h"
class  Client {

public:
	Client(int port);
	bool sendData(std::string);
//	void close();
private:
//	SocketClient socket("localhost", 0);
	int port;
};
#endif /* CLIENT_H_ */
