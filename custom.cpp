#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include "start.pb.h"

using namespace std;
using namespace boost::asio;

int main()
{
	io_service ios;
	ip::address addr = ip::address::from_string("127.0.0.1");
	ip::tcp::endpoint ep(addr, 8888);
	
	ip::tcp::socket sock(ios);
	sock.connect(ep);

	iRequest f;
	f.set_name("iRequest_name");
	f.set_family("iRequest_family");
	f.set_country("iRequest_country");	
	string request;
	f.SerializeToString(&request);
	// 发送请求给服务端
	sock.write_some(buffer(request));

	// 接收服务端的请求
	char response[100];
	sock.read_some(buffer(response));
	
	string serstr(response);		
	iResponse s;
	s.ParseFromString(response);
	cout << s.classmate().c_str() << endl;
	cout << s.school().c_str() << endl;
	cout << s.teacher().c_str() << endl;
	
	return 0;
}
