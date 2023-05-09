#include <boost/asio/placeholders.hpp>
#include <iostream>
#include "tcpConnection.h"
#include "tcpServer.h"

void tcpServer::startAccept()
{
    tcpConnection::shrdPtr newConnection{ tcpConnection::createConnection(mIOContext, *this) };

    mAcceptor.async_accept(newConnection->getSocket(), 
        boost::bind(&tcpServer::handleAccept, this, newConnection, boost::asio::placeholders::error));
}

void tcpServer::handleAccept(tcpConnection::shrdPtr newConnection, const boost::system::error_code& error)
{
    if (!error) {
        newConnection->startConn();
    }

    startAccept();
}

std::string tcpServer::getNextCmd()
{
    std::string cmdString { mCommandQueue[0] };

    mCommandQueue.pop_front();

    return cmdString;
}