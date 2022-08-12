#pragma once
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <string>
#include <vector>
#include <tuple>
#include <functional>
#include <optional>
#include <algorithm>
#include <cstdlib>

#ifdef MYKLIBL_EXPORTS
#   ifdef _WINDLL
#       define MYKLIB_API __declspec(dllexport)
#   elif __linux__
#       define MYKLIB_API 
#   endif
#else
#   ifdef _WINDLL
#       define MYKLIB_API __declspec(dllimport)
#   elif __linux__
#       define MYKLIB_API
#   else //何も指定しない
#       define MYKLIB_API 
#       define MYKLIB_API 
#   endif
#endif


namespace tuilib {
    class MYKLIB_API DiffPositions {
        std::vector<std::tuple<uint16_t, uint16_t, std::string>> _data;
    public:
        void clear() {
            _data.clear();
        }

        void push_back(uint16_t row, uint16_t cul, std::string charactor) {
            _data.push_back({row, cul, charactor});
        }

        // 最後の変更点をpop
        std::optional<std::tuple<uint16_t, uint16_t, std::string>> pop() {
            if (_data.empty()) {
                return std::nullopt;
            } else {
                std::optional<std::tuple<uint16_t, uint16_t, std::string>> data
                    = _data.back();
                _data.pop_back();
                return data;
            }
        }
    };

    class MYKLIB_API Screen {
        bool _doReflesh = true; //画面再描画フラグ
        uint16_t _hight = 1;
        uint16_t _width = 1;
        std::vector<std::string> _frameBuffer;
        std::vector<std::string> _preFrameBuffer;
        DiffPositions _diffs;
    private:
        void refleshScreen() {
            //std::system("cls");
            auto h = _hight;
            auto w = _width;
            for (decltype(h) i = 0; i < h; ++i) {
                for (decltype(w) j = 0; j < w; ++j) {
//std::cout << "j=" << j << " i=" << i << std::endl;
                    std::cout << refFrameBuffer(i + 1, j + 1);
                }
                std::cout << std::endl;
            }
            this->_preFrameBuffer = _frameBuffer;
        }

        DiffPositions& getDiffPositions() {
            return _diffs;
        }

        //位置(row,cul)を指定して任意文字(charactor)で書き換える。
        void putc(uint16_t row, uint16_t cul, std::string& charactor) {
            std::cout << "row"  << row << std::endl;
            std::cout << "cul"  << cul << std::endl;
            std::cout << "cul"  + charactor << std::endl;
        }

        void diffOverWrite() {
            while(true) {
                std::optional<std::tuple<uint16_t, uint16_t, std::string>> maybe 
                    = getDiffPositions().pop();
                if (maybe) {
                    auto [row, cul, charactor] = maybe.value();
                    putc(row, cul, charactor);
                } else {
                    break;
                }
            }
            
        }

    public:
        void printScreenBuffer() const {
            for (auto i : _frameBuffer) {
                std::cout << i << std::endl;
            }
        }

        //スクリーンバッファー作成、縦(hight),横(width)のサイズを指定する
        void createFrameBuffer(uint16_t hight, uint16_t width) {
            _hight = hight;
            _width = width;
            _frameBuffer.resize(hight * width);
            _doReflesh = true;
        }

        //任意の位置(row, cul)に任意の字(charactor)を配置
        void setCharactor(
                std::string charactor, uint16_t row, uint16_t cul
                ) noexcept(false) {
            //std::cout << _frameBuffer.size() << std::endl;
            _frameBuffer.at(((row - 1) * _width) + cul - 1) = charactor;
        }

        //任意の位置(row, cul)の文字を返す(読み取り専用)
        const std::string& refFrameBuffer(
                uint16_t row, uint16_t cul) const noexcept(false) {
            //std::cout << "debug row=" << row << " cul=" << cul  << " " << _frameBuffer[((row - 1) * _width) + cul - 1] << std::endl; 
            return _frameBuffer.at(((row - 1) * _width) + cul - 1);
        }

#ifdef TEST__
#include <algorithm>
#endif
        // 空白文字で埋める
        void clearBuffer(std::string blank = " ") {
#ifdef TEST__
            std::fill(frameBuffer.begin(), frameBuffer.end(), blank);
#else
            //std::fill(_frameBuffer.begin(), _frameBuffer.end(), blank);
            _frameBuffer = std::vector<std::string>(_hight * _width, blank);
#endif
        }

        //フレームバッファの内容をコンソールに反映
        void reflectScreen() {
            if (_doReflesh) {
                refleshScreen();
                _doReflesh = false;
            } else {
                diffOverWrite();
            }
        }
    };
}
