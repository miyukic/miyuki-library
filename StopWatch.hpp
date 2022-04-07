#pragma once
#include <Windows.h>

namespace myk::lib {
    namespace util {
        class StopWatch {
            LARGE_INTEGER _freq;
            LARGE_INTEGER _startPoint, _endPoint;
        public:
            StopWatch();
            void start();
            void stop();
            double result();
        };
    }
}
