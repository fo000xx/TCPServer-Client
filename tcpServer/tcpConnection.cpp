#include <boost/asio/placeholders.hpp>
#include <iostream>
#include <thread>
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
        mServer.getCmdQ().push_back(receivedMsg);
    }
    else {
        std::cout << error.message() << '\n';
    }
}

void tcpConnection::writeOutgoing()
{
    //while(mServer.getResponse().empty()) {
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //}
    std::string_view outMessage{ mServer.getResponse() };

    boost::asio::async_write(mSocket, boost::asio::buffer(outMessage), 
        boost::bind(&tcpConnection::handleWrite, shared_from_this(),
        boost::asio::placeholders::error));

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::string response{""};
    mServer.setResponse(response);
}