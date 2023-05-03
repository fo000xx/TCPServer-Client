#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/bind/bind.hpp>

using namespace boost::asio::ip;

class tcpConnection : public std::enable_shared_from_this<tcpConnection>
{
public:
    using shrdPtr = std::shared_ptr<tcpConnection>;

    static shrdPtr createConnection(boost::asio::io_context& ioContext);
    void startConn();
    tcp::socket& getSocket() { return mSocket; }

private:
    tcpConnection(boost::asio::io_context& ioContext)
        : mSocket(ioContext)
    {
    }

    void handleWrite(const boost::system::error_code& errorMessage);
    void readIncoming();
    void readHandler(const boost::system::error_code& error);
    void writeOutgoing();

    tcp::socket mSocket;
    boost::asio::streambuf mReceiveBuffer;
};

#endif