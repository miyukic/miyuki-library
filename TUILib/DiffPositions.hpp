#pragma once

#include <vector>
#include <iostream>
#include <cstdint>
#include <optional>

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
    enum class TextAttribute {
        Default = 0,
        Bold = 1,

    };

    struct DiffProperty {
        uint16_t row;
        uint16_t cul;
        std::string charactor;
        std::vector<TextAttribute> textAttr;
    };

    class MYKLIB_API DiffPositions {
        std::vector<DiffProperty> _data;
    public:
        void clear() {
            _data.clear();
        }

        //デストラクタ
        ~DiffPositions() {
            //std::cout << "~DiffPositions" << std::endl;
            //裏スクリーンバッファを元に戻す
            std::cout << "\033[?1049l" << std::flush;
        }

        //変更点をpush
        void pushBack(uint16_t row, uint16_t cul, std::string charactor, std::vector<TextAttribute> attributes) {
            _data.emplace_back(DiffProperty{row, cul, charactor, attributes});
        }

        // 最後の変更点をpop
        std::optional<DiffProperty> pop() {
            if (_data.empty()) {
                return std::nullopt;
            } else {
                std::optional<DiffProperty> data
                    = _data.back();
                _data.pop_back();
                return data;
            }
        }
    };
}
