#ifndef PIECE_H
#define PIECE_H

#include "valuepiece.h"
#include "teamcolor.h"
#include <string>


namespace stratego {


    /**
     * this class reprensend a Piece, a piece is a case
     * @brief The Piece class
     */
    class Piece{

        const ValuePiece valuePiece_;
        const TeamColor team_;

    public:

        Piece(const ValuePiece valuePiece, const TeamColor team);

        /**
         * getter
         * @brief valuePiece
         * @return ValuePiece
         */
        ValuePiece valuePiece() const;

        /**
         * getter
         * @brief team
         * @return TeamColor
         */
        TeamColor team() const;

        /**
         * check if the piece is movable (getter)
         * @brief movable
         * @return boolean
         */
        bool movable() const;

        /**
         * check if the piece is a flag
         * @brief isDrapeau
         * @return bool
         */
        bool isFlag() const;

        /**
         * check if the piece is a bomb
         * @brief isBombe
         * @return
         */
        bool isBomb() const;

        /**
         * @brief operator ==
         *
         * Operator to check if a piece equal to another
         * Return true if equal else false
         *
         *
         * @param other Piece: other piece to check
         * @return bool
         */
        bool operator==(const Piece & other) const;

        /**
         * @brief operator >
         *
         * Operator to check if a piece superior that the other
         * Return true if superior else false
         *
         * @param other Piece: other piece to check
         * @return bool
         */
        bool operator>(const Piece & other) const;

    };
}

#endif // PIECE_H
