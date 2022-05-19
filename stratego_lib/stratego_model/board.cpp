#include "board.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace stratego {

Board::Board(){
    initializeStartedBoard();
    initializeWaterBoard();
}

Board::Board(std::array<std::string, 2> file) : Board{}
{
    file_ = file;
}

void Board::initializeStartedBoard()
{
    for(int i=4;i<6;i++){
        for(int j=0;j<column_;j++){
            put(Case{CaseType::Ground}, Position(i,j));
        }
    }

}


void Board::initializeWaterBoard()
{
    for(int i=4;i<6;i++){
        for(int j=3;j<column_;j+=4){
            put(Case{CaseType::Water}, Position(i,j));
            put(Case{CaseType::Water}, Position(i,j-1));
        }
    }
}

void Board::initializeBoardPlayer(int numberOfFile)
{
    std::array<std::string, 2> fileChoice;
    if(numberOfFile==1){
        fileChoice = {file_[0], file_[0]};
    }else{
        fileChoice = {file_[0], file_[1]};
    }

    readFile(fileChoice[0], 0, TeamColor::BLUE, true); // team.txt
    int row = row_;
    row--;
    readFile(fileChoice[1], row, TeamColor::RED, false); // otherTeam.txt
}

void Board::readFile(std::string file, int row, TeamColor team, bool upToDown)
{
    std::map<ValuePiece, int> mapPiece = getMapNumberPiece();
    int col=0;
    std::ifstream instream(file);
    std::string line;
     while (instream >> line)
     {
         ValuePiece valPiece =string_to_value_piece(line);
         auto pieceNumber = mapPiece.find(valPiece);
         if(col>=column_ || row>=row_){
             throw std::invalid_argument("Il y a un nombre trop important de piece vers la gauche ou le bas");
         }
         pieceNumber->second = pieceNumber->second-1;
         put(Case{createPiece(valPiece, team)}, Position{row,col});

         col++;
        if (instream.peek() == '\n')
        {
            col=0;
            if(upToDown){
                row++;
            }else{
                row--;
            }

        }
     }
     auto findMap = std::find_if(mapPiece.begin(),
                               mapPiece.end(),
                               [](std::pair<ValuePiece, int> const& piece)
                               {
                                 if(piece.second!=0){
                                      throw std::invalid_argument("La pièce à été ajouté trop de fois/pas assez, modifié le fichier de configuration du jeu. Piece numéro : " + std::to_string(piece.first));
                                 }
                                 return 0;
                               });
    instream.close();
}

 std::array<std::array<std::optional<Case>, Board::column_>,Board::row_> const & Board::board() const{
    return board_;
}

std::optional<Case> Board::getCase(Position pos) const{
    return board_[pos.row()][pos.column()];
}

std::optional<Piece> Board::getPiece(Position pos) const
{
    return board_[pos.row()][pos.column()]->getcurrentPiece();
}

ValuePiece Board::getValuePiece(Position pos) const
{
    return board_[pos.row()][pos.column()]->getcurrentPiece()->valuePiece();
}

bool Board::isCasePiece(Position pos) const{
    return board_[pos.row()][pos.column()]->getType()==CaseType::Army;
}

bool Board::isCaseWater(Position pos) const
{
    return board_[pos.row()][pos.column()]->getType()==CaseType::Water;
}

bool Board::isCaseGround(Position pos) const
{
    return board_[pos.row()][pos.column()]->getType()==CaseType::Ground;
}

CaseType Board::getTypeCase(Position pos) const
{
    return board_[pos.row()][pos.column()]->getType();
}

void Board::put(Case piece, Position pos){
    board_[pos.row()][pos.column()].emplace(piece);
}

void Board::movePiece(Position currentPos, Position newPos){
    std::optional<Case> piece = board_[currentPos.row()][currentPos.column()];
    moveCase(newPos, *piece);
    deleteCase(currentPos);
}

void Board::moveCase(Position pos, const Case &piece){
    board_[pos.row()][pos.column()]->setType(piece.getType());
    board_[pos.row()][pos.column()]->setCurrentPiece(piece.getcurrentPiece().value());
}

void Board::deleteCase(Position position)
{
    board_[position.row()][position.column()]->setType(CaseType::Ground);
    board_[position.row()][position.column()]->resetPiece();
}

bool Board::isCombat(Position position, Position newPosition) const{
    return (getTypeCase(newPosition)==CaseType::Army && !isSameTeam(position, newPosition));
}

bool Board::isSameTeam(Position positionPiece, Position newPosition) const{
    return board_[positionPiece.row()][positionPiece.column()]->getcurrentPiece()->team()== board_[newPosition.row()][newPosition.column()]->getcurrentPiece()->team();
}

bool Board::isSameTeam(Position positionPiece, TeamColor team) const
{
    return board_[positionPiece.row()][positionPiece.column()]->getcurrentPiece()->team()==team;
}

bool Board::isInside(Position pos) const{
    return ((pos.row()>=0 && pos.row()< row_) && (pos.column() >=0 && pos.column()< column_));
}

bool Board::canBePut(Position currentPos, Position newPos) const{
    if(isInside(newPos) && getTypeCase(newPos)!=CaseType::Water){
        if(getTypeCase(newPos)==CaseType::Army){
            return !isSameTeam(currentPos, newPos);
        }
        return true;
    }
    return false;
}

Position Board::newPositionDirection(const Position &pos, Direction dir) const{
    Position positionDirection = to_position(dir);
    positionDirection.move(pos.row(), pos.column());
    return positionDirection;
}

void Board::combat(Position currentPos, Position newPos){
    int ennemyRow = newPos.row();
    int ennemyColumn = newPos.column();
    int actualRow = currentPos.row();
    int actualColumn = currentPos.column();

    std::optional<Piece> piece = board_[actualRow][actualColumn]->getcurrentPiece();
    std::optional<Piece> pieceNewPosition = board_[ennemyRow][ennemyColumn]->getcurrentPiece();

    if(piece > pieceNewPosition){
        movePiece(currentPos, newPos);
    }else if(piece==pieceNewPosition){
        deleteCase(currentPos);
        deleteCase(newPos);
    }else{
        deleteCase(currentPos);
    }
}

Piece Board::createPiece(ValuePiece piece, TeamColor teamColor) const
{
        return Piece {piece, teamColor};
}

std::map<ValuePiece, int> Board::getMapNumberPiece() const
{
    std::map<ValuePiece, int> mapPiece = {
        {ValuePiece::MARECHAL, 1},
        {ValuePiece::GENERAL, 1},
        {ValuePiece::COLONEL, 2},
        {ValuePiece::MAJOR, 3},
        {ValuePiece::COMMANDANT, 4},
        {ValuePiece::LIEUTENANT, 4},
        {ValuePiece::SERGENT, 4},
        {ValuePiece::DEMINEUR, 5},
        {ValuePiece::ECLAIREUR, 8},
        {ValuePiece::ESPIONNE, 1},
        {ValuePiece::DRAPEAU, 1},
        {ValuePiece::BOMBE, 6}
    };
    return mapPiece;
}


}
