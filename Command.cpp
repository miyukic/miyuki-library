#include <iostream>
#include <string>
#include <cstdint>
#include "Command.hpp"


namespace myk {
    void onCommand(const std::string& command, const std::string* const args, uint32_t size) {
    }
}


int main() {
    using namespace myk;
    std::string command = "test";
    std::string args[] = {"s1", "s2", "s3"};
    std::cout << sizeof(args) / sizeof(std::string) << std::endl; 
    myk::onCommand(std::move(command), args, sizeof(args) / sizeof(std::string)); 
}

