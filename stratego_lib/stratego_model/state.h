#ifndef STATE_H
#define STATE_H

namespace stratego {

    /**
     * @brief The State enum
     *
     * Describe the current state of the game
     *
     */
    enum State{
        NOT_STARTED,
        PICK_PIECE,
        MOVE_PIECE,
        UPDATING_BOARD,
        END,
        RESTART
    };
}

#endif // STATE_H
