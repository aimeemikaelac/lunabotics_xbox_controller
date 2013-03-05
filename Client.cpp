#include "socket.h"
#include "Client.h"

#include <iostream>

using namespace std;

Client::Client(int inputPort = 0) {
	port = inputPort;
}

bool Client::sendData(std::string message) {
	SocketClient socket("localhost", port);
	//for(int i=0; i<dataSize; i++) {
	try{
		socket.SendLine(message);
		socket.Close();
	}
	catch(const char* s){
//			cerr << s << endl;
		return false;
	}
	catch (std::string s) {
//		    cerr << s << endl;
		return false;
	}
	catch (...) {
//		    cerr << "unhandled exception\n";
		return false;
	}
	//}
	return true;
}


/*
int main(int argc, char* argv[]) {
  string host=argv[1];
  int port=atoi(argv[2]);
  int i;
  string chr="yo I am the test string: ";
  for(i=3; i<argc; i++) {
	chr.append(" ");
	chr.append(argv[i]);
  }
  cout<<"hello?"<<endl;
  cout<<chr<<endl;
  try {
    SocketClient s(host, port);

    s.SendLine(chr);

    while (1) {
      string l = s.ReceiveLine();
      if (l.empty()) break;
      cout << l;
      cout.flush();
    }

  }
  catch (const char* s) {
    cerr << s << endl;
  }
  catch (std::string s) {
    cerr << s << endl;
  }
  catch (...) {
    cerr << "unhandled exception\n";
  }

  return 0;
}*/
