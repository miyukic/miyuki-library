#include "Tui.hpp"
#include <stdint.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <signal.h>

int32_t interval = 1000;
tuilib::Screen scrn;
uint16_t hight = 50;
uint16_t width = 80;
const std::string BLOCK = "━";

volatile sig_atomic_t e_flag = 0;

void abortHandler(int signum);
void onTimer(void);

void abortHandler(int signum) {
    //std::cout << "\033[?1049l" << std::flush;
    std::cout << "abortHandler" << std::flush;
    exit(0);
}

void onTimer() {
    static int counter = 0;
    try {
        for (auto i = 0; i < hight; ++i) {
            for (auto j = 0; j < width; ++j) {
                scrn.setCharactor(i+1, j+1, std::to_string(counter));
            }
        }
        scrn.reflectScreen();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    ++counter;
}

int main() {
    if (signal(SIGINT, abortHandler) == SIG_ERR) {
        exit(1);
    }
    using namespace tuilib;
    //std::system("cls");
    scrn.createFrameBuffer(hight, width);
    scrn.clearBuffer(BLOCK);
    scrn.cursor = false;
    //scrn.setCharactor("ほ", 3, 3);
    scrn.reflectScreen();
    while (true) {
        onTimer();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
    return 0;
}
