#include "piece.h"

namespace stratego{
Piece::Piece(const ValuePiece valuePiece, const TeamColor team):
    valuePiece_{valuePiece}, team_{team}{}

ValuePiece Piece::valuePiece() const{
    return valuePiece_;
}

TeamColor Piece::team() const{
    return team_;
}

bool Piece::movable() const{
    return !(valuePiece_ == ValuePiece::BOMBE || valuePiece_ == ValuePiece::DRAPEAU);
}

bool Piece::isFlag() const{
    return valuePiece_ == ValuePiece::DRAPEAU;
}

bool Piece::isBomb() const{
    return valuePiece_== ValuePiece::BOMBE;
}

bool Piece::operator==(const Piece & other) const{
    return valuePiece_== other.valuePiece_;
}

bool Piece::operator>(const Piece & other) const{
    if(other.isFlag()){
        return true;
    }
    switch (valuePiece_) {
        case ValuePiece::ESPIONNE:
            return other.valuePiece_==ValuePiece::MARECHAL;
            break;
        case ValuePiece::DEMINEUR:
            bool isBombe = other.isBomb();
            return isBombe|| valuePiece_> other.valuePiece();
            break;
    }
    return valuePiece_ > other.valuePiece();
}





}
