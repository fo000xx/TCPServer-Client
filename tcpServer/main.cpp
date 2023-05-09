#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <functional>
#include <iostream>
#include <thread>
#include <chrono>
#include "tcpServer.h"

using namespace boost::asio::ip;

void printCmd(tcpServer& server)
{
    while (true) {
        //if empty, sleep
        std::cout << server.getNextCmd();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

//std::thread t1(printCmd, std::ref(server));
int main()
{
    try {
    boost::asio::io_context ioContext;
    tcpServer server(1234, ioContext);
    
    std::thread t1([&ioContext]() {
        ioContext.run();
    });

    while (true) {
        auto& cmdQ { server.getCmdQ() };
        if (!cmdQ.empty()) {
            std::cout << "Command: " << cmdQ[0];
            cmdQ.pop_front();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    t1.join();
    } catch (std::exception& exception) {
        std::cout << exception.what() << '\n';
    }

    return 0;
}