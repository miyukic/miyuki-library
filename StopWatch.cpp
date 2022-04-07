#include "StopWatch.hpp"
#include <Windows.h>

namespace myk {
namespace lib {
    namespace util {
        StopWatch::StopWatch() {
            QueryPerformanceFrequency(&_freq);
        }

        void myk::lib::util::StopWatch::start() {
            QueryPerformanceCounter(&this->_startPoint);
        }

        void StopWatch::stop() {
            QueryPerformanceCounter(&this->_endPoint);
        }

        double StopWatch::result() {
            return (static_cast<double>( _endPoint.QuadPart - _startPoint.QuadPart)
                    * 1000.0 / _freq.QuadPart
                   );
        }
    }
}
}
