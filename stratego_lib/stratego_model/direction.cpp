#include "direction.h"
#include "position.cpp"

namespace stratego {
    Position to_position(Direction dir){
        return dir_to_pos[static_cast<int>(dir)];
    }
}
