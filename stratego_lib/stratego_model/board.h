#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <array>
#include "position.h"
#include <map>
#include "case.h"
#include <optional>
#include "direction.h"



/**
 *This class represent the board.
 *The board is a 2D array of Case and its size is 10x10.
 *The board has also an attribute for the row and column, their value is 10 and can't be modified.
 */
namespace stratego {

    class Board{

    public:
        /**
         * the number of row
         * @brief row_
         */
        static const size_t row_=10;
        /**
         * the number of column
         * @brief column_
         */
        static const size_t column_=10;

    private:

        /**
         * Array that contain file name
         * @brief file
        **/
        std::array<std::string, 2> file_ = {"../data/game/team.txt", "../data/game/otherTeam.txt"};

        /**
         * The 2D array of case.
         * @brief board_
         */
        std::array<std::array<std::optional<Case>, column_>,row_> board_;

        /**
         * Place the ground on the board
         * @brief initializeStartedBoard
         */
        void initializeStartedBoard();

        /**
         * Place the water on the board
         * @brief initializeWaterBoard
         */
        void initializeWaterBoard();

    public :
        /**
         * Constructor
         * @brief Board
         */
        Board();

        /**
         * @brief Board
         *
         * DO NOT USE, ONLY FOR TEST
         *
         * @param file
         */
        explicit Board(std::array<std::string, 2> file);

        /**
         * Read the file that contains the piece and put them in the board.
         * @brief initializeStartedBoard
         */
        void initializeBoardPlayer(int numberOfFile);

        /**
         * getter for the 2D array
         * @brief board
         * @return std::array<std::array<Case*, column_>,row_>
         */
        std::array<std::array<std::optional<Case>, column_>,row_> const & board() const;

        /**
         * getter for a Case at a given position
         * @brief getCase
         * @param pos Position: position in the board
         * @return std::optional<Case>
         */
        std::optional<Case> getCase(Position pos) const;

        /**
         * @brief getPiece
         *
         * Getter for a piece at a given position
         *
         * @param pos Position: position in the board
         * @return a piece
         */
        std::optional<Piece> getPiece(Position pos) const;

        /**
         * @brief getValuePiece
         *
         * Getter for the value of a piece at a given position
         *
         * @param pos Position: position in the board
         * @return
         */
        ValuePiece getValuePiece(Position pos) const;

        /**
         * Check if the case at the given position is a piece
         * @brief isCasePiece
         * @param pos Position: position in the board
         * @return bool
         */
        bool isCasePiece(Position pos) const;

        /**
         * Check if the case at the given position is water
         * @brief isCasePiece
         * @param pos Position: position in the board
         * @return bool
         */
        bool isCaseWater(Position pos) const;

        /**
         * Check if the case at the given position is water
         * @brief isCasePiece
         * @param pos Position: position in the board
         * @return bool
         */
        bool isCaseGround(Position pos) const;

        /**
         * Return the type of the case at the given position.
         * @brief isCasePiece
         * @param pos Position: position in the board
         * @return bool
         */
        CaseType getTypeCase(Position pos) const;

        /**
         * Move the piece at the given position to the other position
         * @brief movePiece
         * @param currentPos Position: current position in the board
         * @param newPos Position: new position in the board
         */
        void movePiece(Position currentPos, Position newPos);


        /**
         * Check if the new
         * @brief isCombat
         * @param positionPiece Position: current position in the board
         * @param newPosition Position: new position in the board
         * @return bool
         */
        bool isCombat(Position position,Position newPosition) const;

        /**
         * Check if the pieces at the given positions are from the same team.
         * @brief isSameTeam
         * @param positionPiece Position: current position in the board
         * @param newPosition Position: new position in the board
         * @return bool
         */
        bool isSameTeam(Position positionPiece, Position newPosition) const;

        /**
         * Check if the case at the given position is from the same team.
         * @brief isSameTeam
         * @param positionPiece Position: position in the board
         * @param team TeamColor : the other team
         * @return bool
         */
        bool isSameTeam(Position positionPiece, TeamColor team) const;

        /**
         * Check if the position given is inside the board
         * @brief isInside
         * @param pos Position: position in the board
         * @return bool
         */
        bool isInside(Position pos) const;

        /**
         * Check if we can put the case of currentPos at the newPos
         * @brief canBePut
         * @param currentPos Position: current position in the board
         * @param newPos Position: new position in the board
         * @return bool
         */
        bool canBePut(Position currentPos, Position newPos) const;

        /**
        * Return the new position, the new position = pos + direction
        * @brief newPositionDirection
        * @param pos Position: position in the board
        * @param d Direction: direction of the position
        * @return position
        */
        Position newPositionDirection(const Position & pos, Direction d) const;

        /**
         * Destructor
         */
        ~Board()= default;

        /**
         * The fight between the 2 pieces at the given position.
         * If the piece at the given pos beat the piece at the new pos then the piece will be move
         * otherwise the piece will be remove and replace with ground
         * @brief combat
         * @param currentPos Position: current position in the board
         * @param newPos Position: new position in the board
         */
        void combat(Position currentPos, Position newPos);

        private :

        /**
         * Put the given piece at the given position in the board.
         * @brief put
         * @param piece Case: the case that will be put
         * @param pos Position: position in the board
         */
        void put(Case piece, Position pos);

        /**
         * @brief deleteCase
         *
         * Set a Case at a given position to his default setting
         * With ground and reset a piece that can be on it
         *
         * @param position Position: position in the board
         */
        void deleteCase(Position position);

        /**
         * Replace the case at the given position with ground
         * @brief deleteCase
         * @param position Position : position in the board
         * @param piece Case: that will be move
         */
        void moveCase(Position position, const Case &piece);

        /**
         * @brief createPiece
         *
         * Return a created Piece depending of with value and the team color
         *
         * @param piece ValuePiece : the value of the piece
         * @param teamColor TeamColor : the team color for the piece
         * @return a created piece
         */
        Piece createPiece(ValuePiece piece, TeamColor teamColor) const;

        /**
         * @brief getMapNumberPiece
         *
         * Returns a map containing the number of times the value of a part can be placed
         *
         * @return a map containing number of times the value
         */
        std::map<ValuePiece, int> getMapNumberPiece() const;

        /**
         * @brief readFile
         *
         * Read a file, and convert all string to a Piece and put it into the board
         * If upToDown is true, it's change the order for placing Piece
         * Check if number of Piece is valid for team color
         *
         * @param file std::string: File to read
         * @param row int: the row to start put
         * @param team TeamColor: team for all Piece
         * @param upToDown bool: to know if invert order
         */
        void readFile(std::string file, int row, TeamColor team, bool upToDown);

    };
}

#endif // BOARD_H
