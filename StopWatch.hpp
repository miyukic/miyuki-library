#pragma once
#include <Windows.h>
#ifdef _WIN32
#   define MIYUKI_API __declspec(dllexport)
#endif

namespace myk::lib {
    namespace util {
        class MIYUKI_API StopWatch {
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
