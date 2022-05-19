#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

using namespace stratego;


MainWindow::MainWindow(uiController controller, QWidget * parent) :
    QMainWindow (parent),
    ui (new Ui::MainWindow),
    _uiBoard { new UiBoard },
    _uiController{controller}
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(_uiBoard);
    QPalette palette = ui->labelError->palette();
     palette.setColor(ui->labelError->foregroundRole(), Qt::red);
     ui->labelError->setPalette(palette);
     ui->labelError->setWordWrap(true);

    QObject::connect(
        _uiBoard,
        SIGNAL(resend_value_from_cell(Position)),
        this,
        SLOT(my_on_uiboard_clicked(Position)));

}

MainWindow::~MainWindow()
{
    delete _uiBoard;
    delete ui;
}

void MainWindow::my_on_uiboard_clicked(Position value)
{
    _uiController.play(value, 1);
}

void MainWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    ui->startButton->setVisible(false);
    ui->debugMode->setEnabled(true);
    ui->spinBox->setVisible(false);
    ui->nbChargedFile->setVisible(false);
    _uiController.play(std::optional<Position>(), ui->spinBox->value());
}

void MainWindow::clearTextError()
{
    ui->labelError->setText(QString::fromStdString(""));
}

void MainWindow::update(const stratego::State state, Game & game)
{

    std::string stateString = "Etat courant : ";
    switch(state){
        case State::NOT_STARTED:
            {
            stateString+="PICK_PIECE";
            _uiBoard->initializeBoard(game);
            _uiBoard->setLayoutBoard();
            ui->stateLabel->setText(QString::fromStdString(stateString));
            }
            break;
    case State::PICK_PIECE:
        clearTextError();
        stateString+="MOVE_PIECE";
        ui->stateLabel->setText(QString::fromStdString(stateString));
        _uiBoard->setBorderToPiece(game.getCurrentPosition().value(), game.getBoard().row_, true);
        break;
    case State::MOVE_PIECE:
        clearTextError();
        stateString+="UPDATING_BOARD";
        ui->stateLabel->setText(QString::fromStdString(stateString));
        _uiBoard->setBorderToPiece(game.getCurrentPosition().value(), game.getBoard().row_, false);
        break;
    case State::UPDATING_BOARD:
        _uiBoard->updateBoard(game);
        stateString+="PICK_PIECE";
        ui->stateLabel->setText(QString::fromStdString(stateString));
        break;
    case State::END:
        _uiBoard->updateBoard(game);
        clearTextError();
        stateString+="END";
        ui->stateLabel->setText(QString::fromStdString(stateString));
        _uiController.play(std::optional<Position>(), 0);
        break;
        default:
            break;
    }
}

void MainWindow::update(const std::string &property,  const std::string &message, const Game &game)
{

    std::string mess = message;
    if(property==Game::PROPERTY_IS_FIGHT_BETWEEN_PIECE){
        mess+= "Pièce attaquant : "+ value_piece_to_string(game.getPiece(game.getCurrentPosition().value()).value().valuePiece())+ " ";
        mess+= "Pièce attaqué : "+ value_piece_to_string(game.getPiece(game.getNewPosition().value()).value().valuePiece());
        ui->labelError->setText(QString::fromStdString(mess));
    }else if(property==Game::PROPERTY_REVERSE_DEBUG_MODE){
        _uiBoard->updateBoard(game);
    }else if(property==Game::PROPERTY_END_GAME){
        ui->labelError->setText(QString::fromStdString(mess));
    }else{
         ui->labelError->setText(QString::fromStdString(mess));
    }

}


void MainWindow::on_debugMode_clicked()
{
    _uiController.reverseDebugMode();
}

