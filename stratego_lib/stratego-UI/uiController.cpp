#include "uiController.h"
#include <QDebug>


uiController::uiController(stratego::Game &game): _game{game}{}

void uiController::start(int nbFile)
{
    _game.start(nbFile);
};

void uiController::reverseDebugMode()
{
    //_game.notifyMessage(Game::PROPERTY_REVERSE_DEBUG_MODE, "ok");
    _game.reverseDebugMode();
}

void uiController::play(std::optional<Position> position, std::optional<int> number){
        bool updateBoard = false;
        switch(_game.getState()){
            case NOT_STARTED:
                start(number.value());
                break;
            case PICK_PIECE:
                {
                    if(_game.canBeSelected(position.value())){
                        _game.selectPiece(position.value());
                    }else{
                        _game.notifyMessage(Game::PROPERTY_CAN_BE_SELECTED_ERROR,"La pièce selectionné n'est pas correct");
                    }
                }
                break;
            case MOVE_PIECE:
                {
                    Direction direction = _game.convertPositionToDirection(position.value());
                    if(_game.getPiece(_game.getCurrentPosition().value())->valuePiece()==ValuePiece::ECLAIREUR){
                        int numberOfMove = _game.convertPositionToNumberOfMove(position.value(), direction);
                        if(_game.canBeMoveForEclaireur(direction, numberOfMove)){
                            _game.moveSpecialPiece(direction, numberOfMove);
                            updateBoard = true;
                        }else{
                            _game.notifyMessage(Game::PROPERTY_CAN_BE_MOVE_ERROR, "Le mouvement vers la position selectionné n'est pas possible pour l'éclaireur");
                        }
                    }else{
                        if(_game.canBeMove(direction)){
                             _game.movePiece(direction);
                             updateBoard = true;
                        }else{
                            _game.notifyMessage(Game::PROPERTY_CAN_BE_MOVE_ERROR, "Le mouvement vers la position selectionné n'est pas possible");
                        }
                    }
                }
                break;
            case END:
                {
                    std::string messageEnd = "Le gagnant de la partie est : ";
                    switch(_game.getWinner()){
                        case BLUE:
                            messageEnd+= "le BLEU";
                            break;
                        case RED:
                            messageEnd+= "le ROUGE";
                            break;
                        case NONE:
                            messageEnd+= "AUCUN, c'est une égalité";
                            break;
                    }
                    _game.notifyMessage(Game::PROPERTY_END_GAME, messageEnd);
                }
                break;
            default:
                break;
        }
        if(updateBoard){
            if(_game.getBoard().isCombat(_game.getCurrentPosition().value(), _game.getNewPosition().value())){
                _game.notifyMessage(Game::PROPERTY_IS_FIGHT_BETWEEN_PIECE, "Une bataille entre deux pièces est en cours. Voici les pièces : ");
            }
            _game.play();
        }

}



