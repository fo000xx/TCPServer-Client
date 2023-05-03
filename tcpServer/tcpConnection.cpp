#include <boost/asio/placeholders.hpp>
#include <iostream>
#include "tcpConnection.h"

using shrdPtr = std::shared_ptr<tcpConnection>;

shrdPtr tcpConnection::createConnection(boost::asio::io_context& ioContext)
{
    return shrdPtr(new tcpConnection(ioContext));
}

void tcpConnection::startConn()
{
    readIncoming();
    
    //one to read an inMessage (and do something)
    writeOutgoing();
}

void tcpConnection::handleWrite(const boost::system::error_code& errorMessage)
{
    if (errorMessage) {
        std::cout << errorMessage << '\n';
    }
}

void tcpConnection::readIncoming()
{
    mReceiveBuffer.consume(mReceiveBuffer.size());
    
    boost::asio::async_read_until(mSocket, mReceiveBuffer, '\n', 
            boost::bind(&tcpConnection::readHandler, shared_from_this(), 
            boost::asio::placeholders::error));
}

void tcpConnection::readHandler(const boost::system::error_code& error)
{
    if (!error) {
        std::string_view receivedMsg{ boost::asio::buffer_cast<const char*>(mReceiveBuffer.data()) };
        std::cout << receivedMsg;
    }
    else {
        std::cout << error.message() << '\n';
    }
}

void tcpConnection::writeOutgoing()
{
    std::string outMessage{ "hello from server\n"};

    boost::asio::async_write(mSocket, boost::asio::buffer(outMessage), 
        boost::bind(&tcpConnection::handleWrite, shared_from_this(),
        boost::asio::placeholders::error));
}