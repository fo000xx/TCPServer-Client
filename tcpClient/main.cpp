#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <string_view>
#include "Client.h"

using namespace boost::asio::ip;

int main()
{
    std::string ipAddr("127.0.0.1");
    boost::asio::io_context ioContext;
    Client client1(ipAddr, 1234, ioContext);
    Client client2(ipAddr, 1234, ioContext);
    Client client3(ipAddr, 1234, ioContext);
    client1.sendMessage();
    client2.sendMessage();
    client3.sendMessage();

    return 0;
}