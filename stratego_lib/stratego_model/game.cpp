#include "game.h"
#include <vector>
#include <exception>
#include <algorithm>
#include <stdlib.h>
#include <QDebug>


namespace stratego {

Position position_diretion [] =
{ /*DOWN*/ Position { 1, 0 }, /*UP*/ Position { -1, 0 }, /*LEFT*/Position{0, -1}, /*RIGHT*/Position{0,1} };

Direction direction_position[] = { Direction::BAS, Direction::HAUT, Direction::GAUCHE, Direction::DROITE};


Game::Game(): board_{Board{}}
{}

Game::Game(const Board &board) : board_{board}
{}


bool Game::checkEnd() const
{
    for(int i=0;board_.row_;i++){
        for(int j=0;board_.column_;j++){
            if(board_.isCasePiece(Position{i,j}) && board_.getPiece(Position{i,j})->movable()){
                return false;
            }
        }
    }
    return true;
}

bool Game::checkEndFlag() const
{
    return board_.getPiece(new_position_.value())->isFlag();
}

void Game::play()
{
    if(current_state_!=State::UPDATING_BOARD){
        throw exception::IllegalStateException("L'etat courant n'est pas UPDATING BOARD. Il n'est pas possible de jouer un tour si les informations ne sont pas renseignés", __FILE__, __FUNCTION__, __LINE__);
    }
    if(!current_position_.has_value() || !new_position_.has_value()){
        throw exception::IllegalPositionException("Aucune position n'a ete passe. Impossible d'avancer dans le jeu si les positions ne sont pas initialisés", __FILE__, __FUNCTION__, __LINE__);
    }

    if(board_.isCombat(current_position_.value(), new_position_.value())){
        if(checkEndFlag()){
            ended_ = true;
            winnerGame = currentTeam_;
            board_.combat(current_position_.value(), new_position_.value());
            resetAllPosition();
            changeState(State::END);
            notify(current_state_, *this);
        }else{
            board_.combat(current_position_.value(), new_position_.value());
            if(checkEnd()){
                ended_ = true;
                winnerGame = TeamColor::NONE;
                changeState(State::END);
                resetAllPosition();
                notify(current_state_, *this);
            }else{
                setTeamNextTurn();
                resetAllPosition();
                notify(current_state_, *this);
                changeState(State::PICK_PIECE);
            }
        }
    }else{
        board_.movePiece(current_position_.value(), new_position_.value());
        setTeamNextTurn();
        resetAllPosition();
        notify(current_state_, *this);
        changeState(State::PICK_PIECE);
    }
}

Board & Game::getBoard()
{
    return board_;

}

State Game::getState() const
{
    return current_state_;
}

std::optional<Position> Game::getCurrentPosition() const
{
    return current_position_;
}

std::optional<Position> Game::getNewPosition() const
{
    return new_position_;
}

std::optional<Piece> Game::getPiece(Position position) const
{
    return board_.getPiece(position);
}

TeamColor Game::getCurrentTeam() const
{
    return currentTeam_;
}

bool Game::isInDebugMode() const
{
    return debug_mode_;
}

bool Game::isEnded() const
{
    return ended_;
}

void Game::selectPiece(Position position)
{
    if(!canBeSelected(position)){
        throw exception::IllegalPositionException("La position n'est pas possible d'etre selectionne",  __FILE__, __FUNCTION__, __LINE__);
    }
    if(current_state_!=State::PICK_PIECE){
        throw exception::IllegalStateException("L'etat courant n'est pas PICK_PIECE. Il n'est pas possible de donner une nouvelle Position pour la position courante", __FILE__, __FUNCTION__, __LINE__);
    }
    current_position_.emplace(position);
    new_position_.emplace(position); // on le set pour pouvoir utiliser dans la nouvelle direction
    notify(current_state_, *this);
    changeState(State::MOVE_PIECE);
}


void Game::move(Direction direction)
{
    Position newPos = board_.newPositionDirection(new_position_.value(), direction); // on utilise new_position_ -> car nous permet de ne pas devoir réecrire une méthode pour éclaireur et autres pour déplacement
    if(!board_.canBePut(current_position_.value(), newPos)){
        throw exception::IllegalDirectionException("Les positions rentrés ne sont pas correct. Il ne peuvent pas être déplacé.", __FILE__, __FUNCTION__, __LINE__);
    }
    new_position_.emplace(newPos);
}

void Game::movePiece(Direction direction)
{
    if(current_state_!=State::MOVE_PIECE){
        throw exception::IllegalStateException("L'etat courant n'est pas MOVE_PIECE. Il n'est pas possible de donner une nouvelle Position pour la nouvelle position à ce placer", __FILE__, __FUNCTION__, __LINE__);
    }
    if(board_.getValuePiece(current_position_.value())==ValuePiece::ECLAIREUR){
        throw exception::IllegalPieceException("La pièce choisie est un eclaireur", __FILE__, __FUNCTION__, __LINE__);
    }
    move(direction);
    notify(current_state_, *this);
    changeState(State::UPDATING_BOARD);
}

void Game::moveSpecialPiece(Direction direction, int numberOfMove){
    if(current_state_!=State::MOVE_PIECE){
        throw exception::IllegalStateException("L'etat courant n'est pas MOVE_PIECE. Il n'est pas possible de donner une nouvelle Position pour la nouvelle position a ce placer", __FILE__, __FUNCTION__, __LINE__);
    }
    if(board_.getValuePiece(current_position_.value())!=ValuePiece::ECLAIREUR){
        throw exception::IllegalPieceException("La pièce choisie n'est pas un eclaireur", __FILE__, __FUNCTION__, __LINE__);
    }
    if(numberOfMove==0){
        throw std::invalid_argument("Le nombre choisie est inférieur ou égal à 0");
    }
    for(int i=0;i<numberOfMove;i++){
        move(direction);
    }
    notify(current_state_, *this);
    changeState(State::UPDATING_BOARD);
}

void Game::reverseDebugMode()
{
    debug_mode_ = !debug_mode_;
    notifyMessage(PROPERTY_REVERSE_DEBUG_MODE, "");
}




void Game::setTeamNextTurn()
{
    switch (currentTeam_) {
    case BLUE:
        currentTeam_ = TeamColor::RED;
        break;
    case RED:
        currentTeam_ = TeamColor::BLUE;
        break;
    default:
        throw exception::IllegalTeamException("L'état ne peut pas être différent de rouge ou bleu", __FILE__, __FUNCTION__, __LINE__);
    }
}


bool Game::canBeSelected(Position position) const
{
    if(board_.getTypeCase(position)==CaseType::Army && board_.getPiece(position)->movable() && board_.getPiece(position)->team()==currentTeam_){
        for(int i=0;i<(sizeof(position_diretion)/sizeof (position_diretion[0]));i++){
            Position pos = position_diretion[i];
            pos.move(position.row(), position.column());
            if(board_.canBePut(position, pos)){
                return true;
            }
        }
    }
    return false;
}

bool Game::canBeMove(Direction direction) const
{
    if(current_state_!=State::MOVE_PIECE){
        throw exception::IllegalStateException("L'etat courant n'est pas MOVE_PIECE. Il n'est pas possible de donner une nouvelle Position pour la nouvelle position à ce placer", __FILE__, __FUNCTION__, __LINE__);
    }
    if(direction==Direction::NOT_VALID){
        return false;
    }
    Position courante = current_position_.value();
    Position position = board_.newPositionDirection(courante, direction);
    return board_.canBePut(current_position_.value(), position) && isMovePositionCorrect(position);
}

bool Game::canBeMoveForEclaireur(Direction direction, int numberOfMove) const{
    if(current_state_!=State::MOVE_PIECE){
        throw exception::IllegalStateException("L'etat courant n'est pas MOVE_PIECE. Il n'est pas possible de donner une nouvelle Position pour la nouvelle position à ce placer", __FILE__, __FUNCTION__, __LINE__);
    }
    if(numberOfMove==0){
        return false;
    }
    if(direction==Direction::NOT_VALID){
        return false;
    }
    Position positionCourante = current_position_.value();
    for(int i=0;i<numberOfMove-1;i++){
        positionCourante = board_.newPositionDirection(positionCourante, direction);
        if(!board_.canBePut(current_position_.value(), positionCourante) || board_.getTypeCase(positionCourante)==CaseType::Army){
            return false;
        }
    }
    positionCourante = board_.newPositionDirection(positionCourante, direction);
    return board_.canBePut(current_position_.value(), positionCourante);
}


bool Game::isMovePositionCorrect(Position newPosition) const
{
    for(int i=0;i<(sizeof(position_diretion)/sizeof (position_diretion[0]));i++){
        Position pos = position_diretion[i];
        pos.move(current_position_->row(), current_position_->column());
        if(pos==newPosition){
            return true;
        }
    }
    return false;
}

void Game::start(int nbFile)
{
    if(current_state_!=State::NOT_STARTED){
        throw exception::IllegalStateException("Il n'est pas possible d'initialiser le jeu dans l'état actuelle", __FILE__, __FUNCTION__, __LINE__);
    }

    board_.initializeBoardPlayer(nbFile);
    notify(current_state_, *this);
    winnerGame = {};
    changeState(State::PICK_PIECE);
}

std::string Game::boardToString() const
{
    std::string board = "";
    board += addingHeaderBoard();

    for(int i=0;i<board_.row_;i++){
        for(int j=0;j<board_.column_;j++){
            if(board_.isCasePiece(Position{i,j})){
                if(isInDebugMode()){
                    if(j == 0){
                        board+=std::to_string(i)+"|"+ value_piece_to_string(board_.getPiece(Position{i,j})->valuePiece());
                    }
                    else{
                        board+= " "  + value_piece_to_string(board_.getPiece(Position{i,j})->valuePiece()) ;
                    }
                }else{
                    //std::to_string(j)+"|"
                    if(!board_.isSameTeam(Position{i,j}, currentTeam_)){
                        if(j == 0){
                            board+=std::to_string(i)+"| *";
                        }
                        else{
                            board+="  *";
                        }
                    }else{
                        if(j == 0){
                            board+= std::to_string(i)+"|" + value_piece_to_string(board_.getPiece(Position{i,j})->valuePiece());
                        }
                        else{
                            board+= " " + value_piece_to_string(board_.getPiece(Position{i,j})->valuePiece());
                        }
                    }
                }
            }else if(board_.isCaseWater(Position{i,j})){
                if(j == 0){
                    board+=std::to_string(i)+"| W";
                }
                else{
                    board+="  W";
                }
            }else{
                if(j == 0){
                    board+= std::to_string(i)+"|  ";
                }
                else{
                    board+="   ";
                }
            }
        }
        board += "\n";
    }
    return board;
}

std::vector<std::vector<std::string>> Game::boardStringArray() const
{
    std::vector<std::vector<std::string>> boardToArray;
    for(int i=0;i<10;i++){
        std::vector<std::string> tmpArray;
        for(int j=0;j<10;j++){
            if(board_.isCasePiece(Position{i,j})){
                if(isInDebugMode()){
                    std::string valuePiece = value_piece_to_string(board_.getPiece(Position{i,j})->valuePiece());
                    valuePiece.erase(std::remove_if(valuePiece.begin(), valuePiece.end(), ::isspace), valuePiece.end());
                    tmpArray.push_back(valuePiece);
                }else{
                    if(!board_.isSameTeam(Position{i,j}, currentTeam_)){
                        tmpArray.push_back("*");
                    }else{
                        std::string valuePiece = value_piece_to_string(board_.getPiece(Position{i,j})->valuePiece());
                        valuePiece.erase(std::remove_if(valuePiece.begin(), valuePiece.end(), ::isspace), valuePiece.end());
                        tmpArray.push_back(valuePiece);
                    }
                }
            }else if(board_.isCaseWater(Position{i,j})){
                tmpArray.push_back("W");
            }else{
                tmpArray.push_back(" ");
            }
        }
        boardToArray.push_back(tmpArray);
    }

    return boardToArray;
}


std::string Game::addingHeaderBoard() const{
    std::string header = "";
    header += " ";
    for(int i=0;i<board_.row_;i++){
        header+= "  " + std::to_string(i);
    }
    header+="\n";
    for(int i =0; i <= board_.row_;i++){
        header+="---";
    }
    header+="\n";
    return header;
}

TeamColor Game::getWinner() const
{
    return winnerGame;
}

Direction Game::convertPositionToDirection(Position pos) const
{
    if(pos.column()==current_position_->column()){
        if(pos.row() < current_position_->row()){
            return Direction::HAUT;
        }else if(pos.row() > current_position_->row()){
            return Direction::BAS;
        }else{
            return Direction::NOT_VALID;
        }
    }
    if(pos.row()==current_position_->row()){
        if(pos.column() < current_position_->column()){
            return Direction::GAUCHE;
        }else if(pos.column() > current_position_->column()){
            return Direction::DROITE;
        }else{
            return Direction::NOT_VALID;
        }
    }
    return Direction::NOT_VALID;
}

int Game::convertPositionToNumberOfMove(Position pos, Direction direction) const
{
    int numberOfMove=0;
    if(direction==Direction::HAUT || direction==Direction::BAS){
        numberOfMove = abs((pos.row() - current_position_->row()));
    }else{
        numberOfMove = abs((pos.column() - current_position_->column()));
    }
    return numberOfMove;
}

void Game::notifyMessage(const std::string &property, const std::string &message) const
{
    notify(property, message, *this);
}

void Game::resetAllPosition()
{
    if(current_state_!=State::UPDATING_BOARD){
        throw exception::IllegalStateException("Il n'est pas possible de reinitialiser les positions dans cette etat. L'etat doit etre UPDATING_BOARD", __FILE__, __FUNCTION__, __LINE__);
    }
    current_position_.reset();
    new_position_.reset();
}

void Game::changeState(State state)
{
    current_state_ = state;
}
}
