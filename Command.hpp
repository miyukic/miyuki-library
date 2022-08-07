#pragma once
#include "StateComponent.hpp"

namespace myk {
    class CommandState {
    public:
        explicit CommandState() noexcept {
        }
    private:
        StateComponent* OwnerCompo;
    };
}
