#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <iostream>
#include <string>
#include "Client.h"

Client::Client(std::string& ipAddr, int portNum, boost::asio::io_context& ioContext) 
    : mIPAddr{ ipAddr }
    , mPortNum{ portNum }
    , mSocket{ ioContext }
{
    mSocket.connect(tcp::endpoint(address::from_string(mIPAddr), mPortNum));
}

void Client::receiveConfirmation(boost::system::error_code& error)
{
    mReceiveBuffer.consume(mReceiveBuffer.size());

    boost::asio::read(mSocket, mReceiveBuffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << '\n';
    }
    else {
        std::string_view receivedMsg = boost::asio::buffer_cast<const char*>(mReceiveBuffer.data());
        std::cout << receivedMsg << '\n';
    }
}

void Client::sendMessage()
{
    std::string outMessage( "Hello1\n");

    boost::system::error_code sendError;
    boost::asio::write(mSocket, boost::asio::buffer(outMessage), sendError);

    if (!sendError) {
        std::cout << "Client sent hello message!\n";
    }
    else {
        std::cout << "send failed: " << sendError.message() << '\n';
    }

    receiveConfirmation(sendError);
}