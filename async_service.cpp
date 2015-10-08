// Copyright 
// License
// Author: adairjun
// This is used to produce a server, listen port 8888, and use protobuf to get message from client and send message to client 

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include "start.pb.h"

using namespace std;
using namespace boost::asio;
using namespace boost::system;
using namespace boost;

void write_handler(const system::error_code&)
{
  cout << "send msg complete" << endl;
}

void accept_handler(const system::error_code& ec, string response, boost::shared_ptr<ip::tcp::socket> sock_pt)
{
  if (ec) { return; }
  sock_pt->async_write_some(buffer(response), boost::bind(write_handler, _1));
}

int main()
{
  io_service ios;
  ip::address addr = ip::address::from_string("127.0.0.1");
  ip::tcp::endpoint ep(addr, 8888);
  ip::tcp::acceptor acce(ios, ep);
  
  while (true) {
	boost::shared_ptr<ip::tcp::socket> sock_pt(new ip::tcp::socket(ios));
  	//ip::tcp::socket sock(ios);
  	//acce.accept(sock);
	iResponse s;
	s.set_classmate("iResponse_classmate");
	s.set_school("iResponse_school");
	s.set_teacher("iResponse_teacher");
	string response;
	s.SerializeToString(&response);
  
	acce.async_accept(*sock_pt, boost::bind(accept_handler, _1, response, sock_pt));
	/*  	
  	char request[100];
  	sock.read_some(buffer(request));
  	iRequest f;
  	f.ParseFromString(string(request));	
  	cout << f.name().c_str() << endl;
  	cout << f.family().c_str() << endl;
  	cout << f.country().c_str() << endl;
  	sock.write_some(buffer(response));
	*/ 
    // 异步等待	
	ios.run();
  }
  
  return 0;
}
		
