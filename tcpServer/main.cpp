#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <functional>
#include <iostream>
#include <ostream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include "tcpServer.h"

using namespace boost::asio::ip;

void cmdParse(std::string cmd)
{
    //due to scoping, any changes made will reset with the next command.
    std::unordered_map<std::string, std::string> demoMap{
        {"one", "oneone"},
        {"two", "twotwo"},
        {"three", "threethree"}};
    
    std::stringstream cmdStream{cmd };
    std::string command{}, key{}, value{};
    cmdStream >> command >> key;
    
    if (command == "set") {
        cmdStream >> value;
        demoMap.insert({key, value});
    }
    else if (command == "get") {
        auto keyExists {demoMap.find(key)};
        if (keyExists != demoMap.end()) {
            std::string mapValue = (keyExists->first + " " + keyExists->second);
            //return mapValue
        }
    }
    else if (command == "del") {
        auto keyExists {demoMap.find(key)};
        if (keyExists != demoMap.end()) {
            demoMap.erase(key);
            //return success
        }
        else { 
            //return failure 
        } 
    }
    else {
        //return invalid command
    }
    
    //for testing until responses can be returned to client.
    for (auto elem : demoMap) { std::cout << elem.first << " " << elem.second << std::endl; }
    cmdStream.clear();
}

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
            cmdParse(cmdQ[0]);
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