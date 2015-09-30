// Copyright 
// License
// Author: adairjun
// This is used to produce a server, listen port 8888, and use protobuf to get message from client and send message to client 

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "start.pb.h"

using namespace std;
using namespace boost::asio;

int main()
{
	io_service ios;
	ip::address addr = ip::address::from_string("127.0.0.1");
	ip::tcp::endpoint ep(addr, 8888);
	ip::tcp::acceptor acce(ios, ep);
	

	iResponse s;
	s.set_classmate("iResponse_classmate");
	s.set_school("iResponse_school");
	s.set_teacher("iResponse_teacher");
	string response;
	s.SerializeToString(&response);

	while(true)
	{
		ip::tcp::socket sock(ios);
		acce.accept(sock);
		
		char request[100];
		sock.read_some(buffer(request));
		iRequest f;
		f.ParseFromString(string(request));	
		cout << f.name().c_str() << endl;
		cout << f.family().c_str() << endl;
		cout << f.country().c_str() << endl;
		sock.write_some(buffer(response));
	}

	return 0;
}
		
