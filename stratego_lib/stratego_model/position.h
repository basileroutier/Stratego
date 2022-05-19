#ifndef POSITION_H
#define POSITION_H

namespace stratego {

    enum class Direction;

    /**
     * @brief The Position class
     *
     * Represent a Position into/for something
     *
     */
    class Position{

        int row_{0};
        int column_{0};


    public:

        Position() = default;

        Position(int row, int column);

        explicit Position(Direction dir);

        /**
         * @brief row
         *
         * Getter for the row
         *
         * @return the row
         */
        int row() const;

        /**
         * @brief column
         *
         * Getter for the column
         *
         * @return the column
         */
        int column() const;

        /**
         * @brief move
         *
         * Move the current row and column and
         * Addition row with the old one
         * Same for column
         *
         * @param row int: new row position
         * @param column int: new column position
         */
        void move(int row, int column);

        /**
         * @brief operator ==
         *
         * Operator to check if a Position equal to another
         * Return true if equal
         * Else false
         *
         * @param other Position: other position to check
         * @return true if equal
         */
        bool operator==(const Position & other) const;

        /**
         * @brief operator !=
         *
         * Operator to check if a piece not equal to another
         * Return true if NOT equal
         * Else false
         *
         * @param other Position : other postion to check
         * @return true if not equal
         */
        bool operator!=(const Position & other) const;

        ~Position() = default;

    };

}



#endif // POSITION_H
