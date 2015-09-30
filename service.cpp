#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "first.pb.h"

using namespace std;
using namespace boost::asio;

int main()
{
	io_service ios;
	ip::address addr = ip::address::from_string("127.0.0.1");
	ip::tcp::endpoint ep(addr, 8888);
	ip::tcp::acceptor acce(ios, ep);
	
	
	first f;
	f.set_name("first_name");
	f.set_family("first_family");
	f.set_country("first_country");
	string serstr;
	f.SerializeToString(&serstr);

	while(true)
	{
		ip::tcp::socket sock(ios);
		acce.accept(sock);
		sock.write_some(buffer(serstr));
	}

	return 0;
}
		
