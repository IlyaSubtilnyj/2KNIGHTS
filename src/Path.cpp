#include <Path.hpp>

namespace TwoKnights
{

    STEP convert_step(STEP step) {
        return static_cast<STEP>(step xor 0b0011);
    }
}
