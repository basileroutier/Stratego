#ifndef VIEW_H
#define VIEW_H
#include "game.h"

namespace stratego {

    /**
     * @brief The View class
     *
     * Console view that will be used
     *
     */
    class View{
    private:
        Game & model_;

    public:

        /**
         * @brief View
         *
         * Basic constructor that initialize the model
         *
         * @param model Game: the current game
         */
        explicit View(Game & model);

        /**
         * @brief askDirection
         *
         * Ask the direction to the user
         * Convert input to direction
         * And return it
         *
         * @return a direction
         */
        Direction askDirection() const;

        /**
         * @brief askPiecePosition
         *
         * Ask the position for a Piece
         * Convert input to position
         * And return it
         *
         * @return
         */
        Position askPiecePosition() const;

        /**
         * @brief displayBoard
         *
         * Display the board passed in parameter to the view
         *
         * @param boardStr string: the board string
         */
        void displayBoard(const std::string &boardStr) const;

        /**
         * @brief askNumberOfFile
         * Ask the number of file
         * And return it
         * @return number of file
         */
        int askNumberOfFile() const;

        /**
         * @brief displayError
         *
         * Display the error passed in parameter to the view
         *
         * @param error string: the error
         */
        void displayError(const std::string& error) const;

        /**
         * @brief displayCombat
         *
         * Display the figth between two piece
         *
         * @param piece1 Piece: current piece choose
         * @param piece2 Piece: enemy piece chosse
         */
        void displayCombat(Piece piece1, Piece piece2) const;

        /**
         * @brief displayEndGame
         *
         * Display the end of the game with a funny message :)
         *
         */
        void displayEndGame() const;

        /**
         * @brief displayWinner
         *
         * Display the winner of the game with is teamColor
         *
         * @param winner TeamColor: team color of the winner
         */
        void displayWinner(TeamColor winner) const;

        /**
         * @brief askNumberOfMove
         *
         * Ask the number of move for a specific Piece in a direction
         * And return it
         *
         * @param direction
         * @return number of move for a direction
         */
        int askNumberOfMove(Direction direction) const;

        bool askDebugMode() const;

        void displayTeamTurn(TeamColor team) const;

    private:

        /**
         * @brief verifInt
         *
         * Verif the integer passed in the console
         * While the integer is not valid it asking again
         * Return the valid input
         *
         * @return valid input int
         */
        int verifInt(const std::string& message, int start, int end) const;

        /**
         * @brief verifString
         *
         * Verif the string passed in the console
         * While the string is not valid it asking again
         * Return the valid input
         *
         * @return valid input string
         **/
        std::string verifString(const std::string& message) const;
    };


}
#endif // VIEW_H
