#include "catch.hpp"
#include "game.h"

using namespace stratego;

/**
 * Array that contain file name
 * @brief file
**/

std::array<std::string, 2> fileTestTeam = {"../data/test/team.txt", "../data/test/otherTeam.txt"};

TEST_CASE("Default initilization game")
{
    SECTION("Testing default initialization Game")
    {
        Board board{fileTestTeam};
        Game game{board};
        REQUIRE(game.getState()==State::NOT_STARTED);
        game.start(2);
        int numberOfPiece = 0;
        for(int i=0;i<game.getBoard().row_;i++){
            for(int j=0;j<game.getBoard().column_;j++){
                if(game.getPiece(Position{i,j}).has_value()){
                    numberOfPiece++;
                }
            }
        }
        REQUIRE(game.getCurrentTeam()==TeamColor::RED);
        REQUIRE(game.getState()==State::PICK_PIECE);
        REQUIRE(numberOfPiece==80);
    }
}




TEST_CASE("Acces to element in game")
{
    SECTION("Acces to default attribut")
    {
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        REQUIRE(game.getCurrentTeam()==TeamColor::RED);
        REQUIRE(game.getPiece(Position{0,0}).has_value()==true); // check si une pièce est à la position xx
        REQUIRE(game.getPiece(Position{5,0}).has_value()==false); // check qu'il n'y est pas encore de pièce à la position xx
        REQUIRE(game.getState()==State::PICK_PIECE);
    }
}



TEST_CASE("Check if possibilities when launch game")
{
    SECTION("Check if a Piece can be selected")
    {
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        REQUIRE_FALSE(game.canBeSelected(Position{9,0})); // prendre la dernière case pour savoir si on peut la déplacer -> ATTENDU FAUX car pas possible de déplacer
        REQUIRE_FALSE(game.canBeSelected(Position{6,0})); // Prendre une bombe n'est pas correct
        REQUIRE_FALSE(game.canBeSelected(Position{6,4})); // Prendre une piece n'est pas correct -> est un DRAPEAU (pour nos info)
        REQUIRE_FALSE(game.canBeSelected(Position{4,2})); // Prendre de l'eau
        REQUIRE_FALSE(game.canBeSelected(Position{3,0})); // prendre une pièce enemy


        REQUIRE(game.canBeSelected(Position{6,5})); // prendre une pièce allié qui peut être déplacé
    }

    SECTION("Check if a Special Piece (eclaireur) can be move. Every situation")
    {
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.reverseDebugMode();
        game.selectPiece(Position{6,9}); // selection eclaireur
        std::cout << game.canBeMoveForEclaireur(Direction::HAUT, 4);
        REQUIRE_FALSE(game.canBeMoveForEclaireur(Direction::BAS, 1)); // direction pas correct
        REQUIRE_FALSE(game.canBeMoveForEclaireur(Direction::DROITE, 1)); // direction pas correct
        REQUIRE_FALSE(game.canBeMoveForEclaireur(Direction::GAUCHE, 1));
        REQUIRE_FALSE(game.canBeMoveForEclaireur(Direction::HAUT, 0)); // Direction est correct mais le nombre de move est = 0 donc mauvais

        REQUIRE(game.canBeMoveForEclaireur(Direction::HAUT, 1)); // correct
        REQUIRE(game.canBeMoveForEclaireur(Direction::HAUT, 2)); // correct
        REQUIRE(game.canBeMoveForEclaireur(Direction::HAUT, 3)); // correct
        REQUIRE_FALSE(game.canBeMoveForEclaireur(Direction::HAUT, 4)); // pas bon car trouve enemie sur son chemin
        REQUIRE_FALSE(game.canBeMoveForEclaireur(Direction::HAUT, 5)); // Retest si pas bon car trouve enemie sur son chemin
    }


    SECTION("Check if a Piece can be move. Every situation")
    {
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,5}); // selection autre pièce
        REQUIRE_FALSE(game.canBeMove(Direction::BAS));
        REQUIRE_FALSE(game.canBeMove(Direction::DROITE));
        REQUIRE_FALSE(game.canBeMove(Direction::GAUCHE));
        REQUIRE(game.canBeMove(Direction::HAUT));
    }

}



TEST_CASE("Throw in check possibilities in game")
{

    SECTION("Throw in can be move for special Piece")
    {
        Board board{fileTestTeam};
        Game game{board};
        REQUIRE_THROWS(game.canBeMoveForEclaireur(Direction::HAUT, 0)); // Erreur car pas dans le bonne etat
        game.start(2);
        game.selectPiece(Position{6,5}); // selection pas eclaireur
    }


    SECTION("Throw in can be move for Piece")
    {
        Board board{fileTestTeam};
        Game game{board};
        REQUIRE_THROWS(game.canBeMove(Direction::HAUT)); // Erreur car pas dans le bonne etat
        game.start(2);
        game.selectPiece(Position{6,9}); // selection autre pièce
    }
}


TEST_CASE("Emulate a basic game"){

    SECTION("Select a piece into the game. Choice an eclaireur to check if the selection is correct"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        REQUIRE(game.getPiece(game.getCurrentPosition().value())->valuePiece()==ValuePiece::ECLAIREUR);
    }

    SECTION("Move a basic Piece to a Direction."){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,5});
        game.movePiece(Direction::HAUT);
        REQUIRE_FALSE(game.getPiece(Position{5,5}).has_value());
        REQUIRE((game.getNewPosition().value()==Position{5,5}));
    }

    SECTION("Move a special Piece to a Direction. NOT ATTACK"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        game.moveSpecialPiece(Direction::HAUT, 2);
        REQUIRE_FALSE(game.getPiece(Position{4,9}).has_value());
        REQUIRE((game.getNewPosition().value()==Position{4,9}));
    }

    SECTION("Move a special Piece to a Direction. The position to go is on enemy"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        game.moveSpecialPiece(Direction::HAUT, 3);
        REQUIRE((game.getNewPosition().value()==Position{3,9}));
    }

    SECTION("Play a turn player with none attack"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        game.moveSpecialPiece(Direction::HAUT, 2);
        game.play();
        REQUIRE(game.getPiece(Position{4,9}).has_value());
    }

    SECTION("Play a turn player with attack"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        game.moveSpecialPiece(Direction::HAUT, 3);
        REQUIRE(game.getCurrentTeam()==TeamColor::RED);
        game.play();
        REQUIRE_FALSE(game.getPiece(Position{4,9}).has_value());
    }

    SECTION("Play multiple turn player with attack"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        game.moveSpecialPiece(Direction::HAUT, 3);
        game.play();
        game.selectPiece(Position{3,4});
        game.movePiece(Direction::BAS);
        REQUIRE(game.getCurrentTeam()==TeamColor::BLUE);
        game.play();
        REQUIRE_FALSE(game.getPiece(Position{3,4}).has_value());
    }
}

TEST_CASE("Emulate a basic game with TRHOW EXCEPTION"){

    SECTION("Select a Position not inside board"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        REQUIRE_THROWS(game.selectPiece(Position{9,100}));
    }

    SECTION("Select a piece not movable"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        REQUIRE_THROWS(game.selectPiece(Position{6,4}));
    }

    SECTION("Select when not in good state"){
        Board board{fileTestTeam};
        Game game{board};
        REQUIRE_THROWS(game.selectPiece(Position{1,1}));
    }

    SECTION("Move a basic Piece to a Direction. Not in good state"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        REQUIRE_THROWS(game.movePiece(Direction::HAUT));
    }

    SECTION("Move a basic Piece to a Direction. Not is an eclaireur"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        REQUIRE_THROWS(game.movePiece(Direction::HAUT));
    }

    SECTION("Move a special Piece to a Direction. Not in good state"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        REQUIRE_THROWS(game.moveSpecialPiece(Direction::HAUT, 1));
    }

    SECTION("Move a special Piece to a Direction. Select a none eclaireur"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,5});
        REQUIRE_THROWS(game.moveSpecialPiece(Direction::HAUT, 1));
    }

    SECTION("Move a special Piece to a Direction. Number of movement <= 0"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        REQUIRE_THROWS(game.moveSpecialPiece(Direction::HAUT, 0));
    }

    SECTION("Play a turn player. Not in good state"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        game.selectPiece(Position{6,9});
        REQUIRE_THROWS(game.play());
    }


    SECTION("Play a turn player. Not initialize position"){
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        REQUIRE_THROWS(game.play());
        game.selectPiece(Position{6,5});
        REQUIRE_THROWS(game.play());
        game.movePiece(Direction::HAUT);
        REQUIRE_NOTHROW(game.play());
    }

    SECTION("Play all game. DOESN'T WORK BECAUSE MOVE IS NOT INTELLIGENCE"){
        Direction position_diretion [] =
        {Direction::HAUT, Direction::DROITE, Direction::BAS , Direction::GAUCHE};
        Board board{fileTestTeam};
        Game game{board};
        game.start(2);
        /*
        while(!game.isEnded()){
            for(int i=0;i<game.getBoard().row_;i++){
                for(int j=0;j<game.getBoard().column_;j++){
                    if(game.canBeSelected(Position{i,j})){
                        game.selectPiece(Position{i,j});
                        if(game.getPiece(Position{i,j})->valuePiece()==ValuePiece::ECLAIREUR){
                            for(int k=0;k<(sizeof(position_diretion)/sizeof (position_diretion[0]));k++){
                                if(game.canBeMoveForEclaireur(position_diretion[k], 1)){
                                    game.moveSpecialPiece(position_diretion[k], 1);
                                    break;
                                }
                            }

                        }else{
                            for(int k=0;k<(sizeof(position_diretion)/sizeof (position_diretion[0]));k++){
                                if(game.canBeMove(position_diretion[k])){
                                    game.movePiece(position_diretion[k]);
                                    break;
                                }
                            }
                        }
                        game.play();
                        std::cout << game.boardToString() << std::endl;
                    }
                }
            }
        }
       */

    }
}



