#include "Tui.hpp"
#include <stdint.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <stdexcept>

int32_t interval = 1000;
tuilib::Screen scrn;
uint16_t hight = 6;
uint16_t width = 18;
const std::string BLOCK = "━";

void onTimer() {
    static int counter = 0;
    try {
        scrn.setCharactor(std::to_string(counter), 3, 3);
        scrn.reflectScreen();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    ++counter;
}

int main() {
    using namespace tuilib;
    //std::system("cls");
    scrn.createFrameBuffer(hight, width);
    scrn.clearBuffer(BLOCK);
    //scrn.setCharactor("ほ", 3, 3);
    scrn.reflectScreen();
    while (true) {
        onTimer();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
    return 0;
}
