#include <boost/asio/placeholders.hpp>
#include <iostream>
#include "tcpConnection.h"
#include "tcpServer.h"

using shrdPtr = std::shared_ptr<tcpConnection>;

shrdPtr tcpConnection::createConnection(boost::asio::io_context& ioContext, tcpServer& server)
{
    return shrdPtr(new tcpConnection(ioContext, server));
}

void tcpConnection::startConn()
{
    readIncoming();
    
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
    boost::asio::async_read_until(mSocket, mReceiveBuffer, '\n', 
            boost::bind(&tcpConnection::readHandler, shared_from_this(), 
            boost::asio::placeholders::error));
}

void tcpConnection::readHandler(const boost::system::error_code& error)
{
        if (!error) {
        std::string receivedMsg{ boost::asio::buffer_cast<const char*>(mReceiveBuffer.data()) };
        std::cout << receivedMsg;
        mServer.getCmdQ().push_back(receivedMsg);
    }
    else {
        std::cout << error.message() << '\n';
    }
}

void tcpConnection::writeOutgoing()
{
    //output mResponse!
    std::string outMessage{ "hello from server\n"};

    boost::asio::async_write(mSocket, boost::asio::buffer(outMessage), 
        boost::bind(&tcpConnection::handleWrite, shared_from_this(),
        boost::asio::placeholders::error));
}