#include "Tui.hpp"
#include <stdint.h>
#include <thread>
#include <chrono>
#include <cstdlib>
//#include <exception>
//#include <stdexcept>

int32_t interval = 1000;
tuilib::Screen scrn;
uint16_t hight = 6;
uint16_t width = 18;
const std::string BLOCK = "■";

void onTimer() {
    static int counter = 0;
    scrn.setCharactor(std::to_string(counter), 3, 3);
    ++counter;
}

int main() {
    using namespace tuilib;
    //std::system("cls");
    scrn.createFrameBuffer(4, 4);
    scrn.clearBuffer("■");
    //scrn.setCharactor("ほ", 3, 3);
    scrn.reflectScreen();
    //while (true) {
    //    //onTimer();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    //}
    return 0;
}
