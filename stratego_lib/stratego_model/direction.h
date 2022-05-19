#ifndef DIRECTION_H
#define DIRECTION_H

#include "position.h"

namespace stratego {

    /**
     * This class represent a direction. There are only 4 directions
     * @brief The Direction enum
     */
    enum class Direction{
        HAUT,
        BAS,
        GAUCHE,
        DROITE,
        NOT_VALID
    };

    /**
         * Convert the direction to a position
         * @brief to_position
         * @param dir
         * @return
         */
        Position to_position(Direction dir);


}
#endif // DIRECTION_H
