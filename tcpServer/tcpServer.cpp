#include <boost/asio/placeholders.hpp>
#include "tcpConnection.h"
#include "tcpServer.h"

void tcpServer::startAccept()
{
    tcpConnection::shrdPtr newConnection{ tcpConnection::createConnection(mIOContext) };

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