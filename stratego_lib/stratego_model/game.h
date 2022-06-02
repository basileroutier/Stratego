#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <vector>
#include "state.h"
#include "observable.h"
#include <string>
#include "position.h"
#include "illegalPositionException.hpp"
#include "illegalStateException.hpp"
#include "illegalDirectionException.hpp"
#include "illegalPieceException.hpp"
#include "illegalTeamException.hpp"


namespace stratego {

    /**
     * This class is the model of the app
     * @brief The Game class
     */
    class Game : public utils::Observable{

    public:

        inline static std::string PROPERTY_CAN_BE_SELECTED_ERROR="game.canBeSelectedError";
        inline static std::string PROPERTY_CAN_BE_MOVE_ERROR="game.canBeMoveError";
        inline static std::string PROPERTY_IS_FIGHT_BETWEEN_PIECE="game.isFightBetweenPiece";
        inline static std::string PROPERTY_REVERSE_DEBUG_MODE="game.reverseDebugMode";
        inline static std::string PROPERTY_END_GAME="game.endGameOver";
        inline static std::string PROPERTY_SHUFFLE_GAME= "game.shufflePiece";


    private:

        bool ended_ = false;
        bool debug_mode_ = false;
        TeamColor currentTeam_ = TeamColor::RED;
        Board board_;
        State current_state_= State::NOT_STARTED;
        std::optional<Position> current_position_;
        std::optional<Position> new_position_;
        TeamColor winnerGame = TeamColor::NONE;

    public:
        /**
         * Constructor
         * @brief Game
         */
        Game();

        /**
         * @brief Game
         *
         * DO NOT USE, CONSTRUCTOR FOR TEST ONLY
         *
         * @param board
         */
        explicit Game(const Board &board);

        /**
         * check if the game is ended
         * @brief checkEnd
         * @return
         */
        bool checkEnd() const;

        /**
         * check if the game is ended
         * @brief checkEnd
         * @return
         */
        bool checkEndFlag() const;

        /**
         * Represent the loop of the game ex : turn of player x, move, check end, turn  of play x2...
         * @brief play
         */
        void play();

        /**
         * getter
         *  @brief getBoard
         * @return Board
         */
        Board & getBoard();

        /**
         * @brief getState
         *
         * Getter of the current state
         *
         * @return State
         */
        State getState() const;

        /**
         * @brief getCurrentPosition
         *
         * Getter for the current position
         *
         * @return current position
         */
        std::optional<Position> getCurrentPosition() const;

        /**
         * @brief getNewPosition
         *
         * Getter for the new Position selected
         *
         * @return the new position selected
         */
        std::optional<Position> getNewPosition() const;

        /**
         * @brief getPiece
         *
         * Getter for a std::optional<Piece> into the board at a specific position
         *
         * @param position Position : Position that will be used
         * @return std::optional<Piece> into the board
         */
        std::optional<Piece> getPiece(Position position) const;

        /**
         * @brief getCurrentTeam
         *
         * Getter for the current player turn
         *
         * @return TeamColor
         */
        TeamColor getCurrentTeam() const;

        /**
         * getter for it is debug mode
         * @brief isInDebugMode
         * @return bool
         */
        bool isInDebugMode() const;

        /**
         * getter if it is the end of the game
         * @brief isEnded
         * @return bool
         */
        bool isEnded() const;

        /**
         * setter for the current pos
         * @brief setCurrentPosition
         * @param position
         */
        void selectPiece(Position position);

        /**
         * @brief reverseDebugMode
         *
         * Setter for debug mode. It set the inverse of current debug mode option
         *
         */
        void reverseDebugMode();

        /**
         * setter for the new position
         * @brief setNewPosition
         * @param direction Direction: the direction
         */
        void movePiece(Direction direction);

        /**
         * @brief setNewPositionEclaireur
         *
         * Setter the new position for a specific case with the number of move
         *
         * @param direction Direction: direction to move
         * @param numberOfMove int: number of move
         */
        void moveSpecialPiece(Direction direction, int numberOfMove);



        /**
         * check if the piece at the given position can be selected
         * @brief canBeSelected
         * @param position
         * @return bool
         */
        bool canBeSelected(Position position) const;

        /**
         * check if the piece at the current pos can be moved to the new Position
         * @brief canBeMove
         * @param direction
         * @return boolk
         */
        bool canBeMove(Direction direction) const;

        /**
         * @brief canBeMoveForEclaireur
         *
         * Check if the eclaireur can be move with the number of move
         * Return false if it find water or enemy during visit
         * Otherwise return true
         *
         * @param direction Direction: direction to check move
         * @param numberOfMove int: number of move in the selected direction
         * @return bool
         */
        bool canBeMoveForEclaireur(Direction direction, int numberOfMove) const;



        /**
         * call the method initializeboardpiece of the board
         * @brief start
         * @param nbFile
         */
        void start(int nbFile);


        /**
         * call the method initializeboardpiece of the board
         * @brief restart
         * @param nbFile
         */
        void restart(int nbFile);

        /**
         * Convert the board to a string
         * @brief boardToString
         * @return string
         */
        std::string boardToString() const;

        /**
         * Convert the board to a string
         * @brief boardStringArray
         * @return string
         */
        std::vector<std::vector<std::string> > boardStringArray() const;


        /**
         * return the winner of the game wooohoooo
         * @brief getWinner
         * @return int
         */
        TeamColor getWinner() const;

        /**
         * @brief convertPositionToDirection
         * @param pos
         * @return Direction
         *
         * Convert a position to a direction
         */
        Direction convertPositionToDirection(Position pos) const;

        /**
         * @brief convertPositionToNumberOfMove
         * @param pos
         * @param direction
         * @return int
         * Return the number of move necessary to go to the given position with the given direction
         */
        int convertPositionToNumberOfMove(Position pos, Direction direction) const;


        void shufflePiecesPlayer();

        /**
         * @brief notifyMessage
         * @param property
         * @param message
         * notify some classes by calling their update method (the class who are observer are called)
         */
        void notifyMessage(const std::string& property, const std::string& message) const;




    private:

        std::vector<Position> getAllPositionFromCurrentPlayer();

        void resetAllPosition();

        /**
         * @brief setDirectionToPosition
         *
         * Convert direction to the new Position
         *
         * @param direction Direction: the direction to go
         */
        void move(Direction direction);

        /**
         * @brief setTeamNextTurn
         *
         * Set the next turn to next team
         *
         */
        void setTeamNextTurn();


        /**
         * change the state of the game
         * @brief changeState
         * @param state
         */
        void changeState(State state);

        /**
         * @brief isMovePositionCorrect
         *
         * Check foreach direction (up, down, left, right) if the position is the same than the current_position
         *
         * @param newPosition Position: position that will be check foreach direction
         * @return bool
         */
        bool isMovePositionCorrect(Position newPosition) const;

        /**
         * @brief addingHeaderBoard
         * @return String
         * add a header to the board and return it.
         */
        std::string addingHeaderBoard() const;
    };
}

#endif // GAME_H
