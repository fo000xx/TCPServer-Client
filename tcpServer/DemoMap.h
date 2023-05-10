#ifndef DEMOMAP_H
#define DEMOMAP_H

#include <unordered_map>
#include <string>

namespace gDemoMap
{
    std::unordered_map<std::string, std::string> DemoMap{ //shouldn't define this in a .h, for POC only.
        {"one", "oneone"},
        {"two", "twotwo"},
        {"three", "threethree"}};
}

#endif