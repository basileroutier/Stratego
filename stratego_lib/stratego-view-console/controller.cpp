#include "controller.h"

namespace stratego {

Controller::Controller(Game &model, View &view): model_{model}, view_{view}, nbFile_{1}{}

void Controller::start()
{
    if(view_.askDebugMode() == 1){
        model_.reverseDebugMode();
    }
    int nbFile = view_.askNumberOfFile();
    model_.start(nbFile);
    view_.displayBoard(model_.boardToString());
}

void Controller::play()
{
    bool isFinish = false;
    while(!isFinish){
        switch(model_.getState()){
            case NOT_STARTED:
                start();
                break;
            case PICK_PIECE:
            {
                view_.displayTeamTurn(model_.getCurrentTeam());
                Position pos = view_.askPiecePosition();
                model_.selectPiece(pos);
                }break;
            case MOVE_PIECE:{
                Direction direction = view_.askDirection();
                if(model_.getPiece(model_.getCurrentPosition().value())->valuePiece()==ValuePiece::ECLAIREUR){
                    int numberOfMove = view_.askNumberOfMove(direction);
                    model_.moveSpecialPiece(direction, numberOfMove);
                }else{
                    model_.movePiece(direction);
                }
                }break;
            case UPDATING_BOARD:{
                if(model_.getBoard().isCombat(model_.getCurrentPosition().value(), model_.getNewPosition().value())){
                    view_.displayCombat(model_.getPiece(model_.getCurrentPosition().value()).value(), model_.getPiece(model_.getNewPosition().value()).value());
                }
                model_.play();
                view_.displayBoard(model_.boardToString());
            }break;
            case END:
                view_.displayEndGame();
                isFinish = true;
                break;
            }
    }
}

}
