#include "position.h"

namespace stratego {

static Position dir_to_pos [] =
{ /*UP*/ Position { -1, 0 }, /*DOWN*/ Position { 1, 0 }, /*LEFT*/Position{0, -1}, /*RIGHT*/Position{0,1} };

Position::Position(int row, int column): row_{row}, column_{column}{}

Position::Position(Direction dir): Position{dir_to_pos[static_cast<int>(dir)]}{}

int Position::row() const{
    return row_;
}

int Position::column() const{
    return column_;
}

void Position::move(int row, int column){
    row_+=row;
    column_+=column;
}

bool Position::operator==(const Position & other) const{
    return (row() == other.row() && column() == other.column());
}

bool Position::operator!=(const Position &other) const
{
    return (row() != other.row() && column() != other.column());
}
}
