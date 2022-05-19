#include "case.h"

namespace stratego {

Case::Case(CaseType caseType) : type{caseType}{}

Case::Case(Piece piece): type{CaseType::Army}, currentPiece{piece}{}

CaseType Case::getType() const
{
    return type;
}

std::optional<Piece> Case::getcurrentPiece() const
{
    return currentPiece;
}

void Case::setType(CaseType type)
{
    this->type = type;
}

void Case::setCurrentPiece(Piece piece)
{
    currentPiece.emplace(piece);
}

void Case::resetPiece()
{
    currentPiece.reset();
}

}



