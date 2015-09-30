#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include "first.pb.h"

using namespace std;
using namespace boost::asio;

int main()
{
	io_service ios;
	ip::address addr = ip::address::from_string("127.0.0.1");
	ip::tcp::endpoint ep(addr, 8888);
	
	ip::tcp::socket sock(ios);
	sock.connect(ep);

	char str[100];
	sock.read_some(buffer(str));
	
	string serstr(str);		
	first f;
	f.ParseFromString(str);
	cout << f.name().c_str() << endl;
	
	return 0;
}
