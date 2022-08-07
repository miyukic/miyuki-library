#pragma once
#include <string>
#include <vector>

namespace tuilib {
    class Screen {
    private:
        uint32_t hight = 0;
        uint32_t width = 0;
        std::vector<char> frameBuffer;

    public:
        inline void createFrameBuffer(uint32_t hight, uint32_t width) {
            frameBuffer.resize(hight).
        }

        inline void setCharactor(char charactor, uint32_t row, uint32_t cul) {
            frameBuffer.at(row).at(cul) = charactor;
        }

        //フレームバッファの内容をコンソールに反映
        inline void reflectScreen() {
        }
    };
}
