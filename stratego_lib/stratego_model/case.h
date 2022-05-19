#ifndef CASETEST_H

#define CASETEST_H
#include "casetype.h"
#include "piece.h"
#include <optional>

namespace stratego {

    /**
     * @brief The Case class
     *
     * Case can contain a part and contains a type to know of which type the box is
     *
     */
    class Case{

        CaseType type;
        std::optional<Piece> currentPiece;

    public:

        /**
         * @brief Case
         *
         * Simple constructor with caseType but without a Piece
         *
         * @param caseType CaseType: the type of the case
         */
        explicit Case(CaseType caseType);

        /**
         * @brief Case
         *
         * Simple constructor with piece but without a CaseType because
         * It's already an Army
         *
         * @param piece Piece: the piece
         */
        explicit Case(Piece piece);

        /**
         * @brief getType
         *
         * return the type of the case
         *
         * @return the type of the case
         */
        CaseType getType() const;

        /**
         * @brief getcurrentPiece
         *
         * return the current piece into the Case
         *
         * @return the current piece into the Case
         */
        std::optional<Piece> getcurrentPiece() const;

        /**
         * @brief setType
         *
         * Set the type of a Case
         *
         * @param type CaseType: type of the Case
         */
        void setType(CaseType type);

        /**
         * @brief setCurrentPiece
         *
         * Set the current piece to a new piece
         *
         * @param piece Piece: the new piece that will be placed
         */
        void setCurrentPiece(Piece piece);

        /**
         * @brief resetPiece
         * Reset the current piece without any
         */
        void resetPiece();

    };

}

#endif // CASETEST_H
