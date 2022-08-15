#pragma once
#include <cstddef>
//#include <errhandlingapi.h>
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

#include "DiffPositions.hpp"

#ifdef _WIN32
#   include <Windows.h>
#   include <io.h>
#endif

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

    class MYKLIB_API Screen {
        bool _doReflesh = true; //画面再描画フラグ
        uint16_t _hight = 1;
        uint16_t _width = 1;
        std::vector<std::string> _frameBuffer;
        std::vector<std::string> _preFrameBuffer;
        DiffPositions _diffs;
    public:
        bool cursor = true;
    private:
        void refleshScreen() {
            std::cout << "\033[?1049h" << "\033[1d" << "\033[1G" << std::flush;
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
        void putc(const DiffProperty& dp) {
            std::cout << "\033[" << dp.row << "d" << std::flush;
            std::cout << "\033[" << dp.cul << "G" << std::flush;
            std::cout << dp.charactor << std::flush;
        }

        //差分を書き換える。
        void diffOverWrite() {
            while(true) {
                std::optional<DiffProperty> maybe 
                    = getDiffPositions().pop();
                if (maybe) {
                    auto diffproperty{maybe.value()};
                    putc(diffproperty);
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
#ifdef _WIN32
            //if (_isatty(1)) {
            //    if (SetConsoleMode(
            //                GetStdHandle(STD_OUTPUT_HANDLE),
            //                ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
            //        //std::cerr << GetLastError() << std::endl;
            //    }
            //}
#endif
        }

        //任意の位置(row, cul)に任意の字(charactor)を配置, textattrに文字色等の設定を配列(vector)で渡す
        void setCharactor(
                uint16_t row, uint16_t cul, const std::string& charactor, const std::vector<TextAttribute>& txtattr = {} 
                ) noexcept(false) {
            //std::cout << _frameBuffer.size() << std::endl;
            _frameBuffer.at(((row - 1) * _width) + cul - 1) = charactor;
            _diffs.pushBack(row, cul, charactor, txtattr);
        }

        struct Propaty {

        };

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
            if (cursor) {
                std::cout << "\033[?25h" << std::flush;
            } else {
                std::cout << "\033[?25l" << std::flush;
            }
            if (_doReflesh) {
                refleshScreen();
                _doReflesh = false;
            } else {
                diffOverWrite();
            }
            _diffs.clear();
        }
    };
}
