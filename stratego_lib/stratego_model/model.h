#ifndef MODEL_H
#define MODEL_H

#include "Board.h"
#include "TeamColor.h"
#include "State.h"



namespace stratego {

    class Game{

        bool is_ended_ = false;
        bool is_debug_mode_ = false;
        TeamColor currentTeam_ = TeamColor::RED;
        Board board_;

    public:
        Game();

        bool checkEnd();

        void play();

        Board getBoard();
    private:
        void initializeStartedGame(std::string red, std::string blue);

    };

}

#endif // MODEL_H
