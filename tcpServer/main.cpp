#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <iostream>
#include "tcpServer.h"

using namespace boost::asio::ip;

int main()
{
    try {
    boost::asio::io_context ioContext;
    tcpServer server(1234, ioContext);
    ioContext.run();
    } catch (std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
    
    return 0;
}