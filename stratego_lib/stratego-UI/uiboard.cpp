#include "uiboard.h"

#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>

void UiBoard::initializeBoard(Game & game)
{
    unsigned width=70;
    unsigned heigth=60;
    QColor colorGreen{22, 110, 26};

    auto gameTest = game.boardStringArray();
    for(int i=0;i<gameTest.size();i++){
        for(int j=0;j<gameTest.at(0).size();j++){
            if(gameTest.at(i).at(j)=="W"){
                initializeOneCellOnBoard(j, i, width, heigth, QColor{68, 125, 194}, std::optional<std::string>());
            }else if(gameTest.at(i).at(j)==" "){
                initializeOneCellOnBoard(j, i, width, heigth, colorGreen, std::optional<std::string>());
            } else if(gameTest.at(i).at(j)=="*"){
                std::string imageName = "default";
                if(game.getCurrentTeam()==TeamColor::BLUE){
                    imageName+="R";
                }else if(game.getCurrentTeam()==TeamColor::RED){
                    imageName+="B";
                }
                initializeOneCellOnBoard(j, i, width, heigth, colorGreen, imageName);
            }else{
                std::string imageName = gameTest.at(i).at(j);
                if(game.getCurrentTeam()==TeamColor::BLUE){
                    imageName+="B";
                }else if(game.getCurrentTeam()==TeamColor::RED){
                    imageName+="R";
                }
                initializeOneCellOnBoard(j, i, width, heigth, colorGreen, imageName);
            }
        }
    }
}

void UiBoard::initializeOneCellOnBoard(int j, int i, unsigned width, unsigned heigth, QColor color, std::optional<std::string> nameImage)
{
    if(nameImage.has_value()){
        _cells.push_back(
            new UiCellPiece(
                j,
                i,
                Position{i,j}, width, heigth, color, nameImage.value(), true));
    }else{
        _cells.push_back(
            new UiCellPiece(
                j,
                i,
                Position{i,j}, width, heigth, color));
    }

}


auto UiBoard::setSignalToButton()
{
    // place cells on scene
    // each signal emit from ghexacell is reimit… mainwindow3 will use it
    auto scene = new QGraphicsScene();
    std::for_each(begin(_cells),
                  end(_cells),
    [this, scene] (UiCellPiece * e) {
        e->setPos((e->x()), (e->y()));
        scene->addItem(e);
        QObject::connect(
            e,
            SIGNAL(sendValue(Position)),
            this,
            SIGNAL(resend_value_from_cell(Position)));

    });
    return scene;
}



void UiBoard::setLayoutBoard()
{
    auto view = new QGraphicsView(setSignalToButton());
    view->update();
    auto layout = new QHBoxLayout();
    layout->addWidget(view);
    this->setLayout(layout);
}

void UiBoard::setBorderToPiece(Position pos, int posMax, bool isBorder)
{
    int positionToIndex = (pos.row()*posMax) + pos.column();
    _cells.at(positionToIndex)->setBorder(isBorder);
}

void UiBoard::updateBoard(const Game &game)
{
    auto gameTest = game.boardStringArray();

    int rowCol = 0;
    for(int i=0;i<gameTest.size();i++){
        for(int j=0;j<gameTest.at(0).size();j++){
            if(gameTest.at(i).at(j)=="W"){
                _cells.at(rowCol)->setImageNamePiece("");
                _cells.at(rowCol)->withPiece(false);
            }else if(gameTest.at(i).at(j)==" "){
                _cells.at(rowCol)->setImageNamePiece("");
                _cells.at(rowCol)->withPiece(false);
            } else if(gameTest.at(i).at(j)=="*"){
                std::string imageName = "default";
                if(game.getCurrentTeam()==TeamColor::BLUE){
                    imageName+="R";
                }else if(game.getCurrentTeam()==TeamColor::RED){
                    imageName+="B";
                }
                _cells.at(rowCol)->setImageNamePiece(imageName);
                _cells.at(rowCol)->withPiece(true);
            }else{
                std::string imageName = gameTest.at(i).at(j);
                if(game.getPiece(Position{i,j})->team()==TeamColor::BLUE){
                    imageName+="B";
                }else if(game.getPiece(Position{i,j})->team()==TeamColor::RED){
                    imageName+="R";
                }
                _cells.at(rowCol)->setImageNamePiece(imageName);
                _cells.at(rowCol)->withPiece(true);
            }
            rowCol++;
        }
    }
}

UiBoard::UiBoard() :
    QWidget(),
    _cells {}
{}


