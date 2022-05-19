#include "catch.hpp"
#include "board.h"

using namespace stratego;


/**
 * Array that contain file name
 * @brief file
**/
std::array<std::string, 2> fileTest = {"../data/test/team.txt", "../data/test/otherTeam.txt"};

TEST_CASE("Testing board instanciation")
{
    SECTION("Testing default initialization Board")
    {
        Board board{fileTest};
        bool hasNoValue = false, hasGround=false, hasWater = false;
        for(int i=0;i<board.row_;i++){
            for(int j=0;j<board.column_;j++){
                if(!board.getCase(Position{i,j}).has_value() && !hasNoValue){
                    hasNoValue = true;
                }else{
                    if(board.getTypeCase(Position{i,j})==CaseType::Ground && !hasGround){
                        hasGround = true;
                    }else if(!hasWater){
                        hasWater = true;
                    }
                }

            }
        }
        REQUIRE(hasGround);
        REQUIRE(hasNoValue);
        REQUIRE(hasWater);
    }

    SECTION("Testing initialization of the Piece in the board")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        bool hasNoValue = false, hasGround=false, hasWater = false, hasPiece = false;
        int numberOfPiece = 0, numberOfWater = 0;

        for(int i=0;i<board.row_;i++){
            for(int j=0;j<board.column_;j++){
                if(!board.getCase(Position{i,j}).has_value()){
                    hasNoValue = true;
                }else{
                    CaseType typeCase = board.getTypeCase(Position{i,j});
                    if(typeCase==CaseType::Ground){
                        hasGround = true;
                    }else if(typeCase==CaseType::Water){
                        hasWater = true;
                        numberOfWater++;
                    }else if(typeCase==CaseType::Army){
                        hasPiece = true;
                        numberOfPiece++;
                    }
                }

            }
        }
        REQUIRE(hasGround);
        REQUIRE(!hasNoValue);
        REQUIRE(hasWater);
        REQUIRE(hasPiece);

        REQUIRE(numberOfPiece==80);
        REQUIRE(numberOfWater==8);
    }
}

TEST_CASE("Acces to element in array")
{
    SECTION("Acces to Case not empty for Piece, Ground and Water in the board")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        bool hasValue = board.getCase(Position{0,0}).has_value() && board.getCase(Position{5,0}).has_value() && board.getCase(Position{5,3}).has_value();
        REQUIRE(hasValue);
    }

    SECTION("Acces to TypeCase of the board")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        bool hasValue = board.getTypeCase(Position{0,0})==CaseType::Army && board.getTypeCase(Position{5,0})==CaseType::Ground && board.getTypeCase(Position{5,3})==CaseType::Water;
        REQUIRE(hasValue);
    }

    SECTION("Acces to Piece in two team in the board")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        bool hasPiece = board.getCase(Position{3,0})->getcurrentPiece().has_value() && board.getCase(Position{6,0})->getcurrentPiece().has_value();
        REQUIRE(hasPiece);
    }

    SECTION("Acces to empty Piece in two team in the board")
    {
        Board board{fileTest};
        bool hasPiece = board.getPiece(Position{3,0}).has_value() && board.getPiece(Position{6,0}).has_value();
        REQUIRE(!hasPiece);
    }

    SECTION("Acces to ValuePiece of a Piece in two team in the board")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        bool isValueBombe = board.getValuePiece(Position{3,0})==ValuePiece::BOMBE && board.getValuePiece(Position{6,0})==ValuePiece::BOMBE;
        REQUIRE(isValueBombe);
    }
}


TEST_CASE("Check possiblities in Board")
{
    SECTION("Check if case have a Piece")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        REQUIRE(board.isCasePiece(Position{0,0}));
    }

    SECTION("Check if case have not a Piece")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        REQUIRE(!board.isCasePiece(Position{5,0}));
    }

    SECTION("Check if case is Water")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        REQUIRE(board.isCaseWater(Position{5,3}));
    }

    SECTION("Check if case is not Water")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        REQUIRE(!board.isCaseWater(Position{8,3}));
    }


    SECTION("Check if two Piece is in same Team with two position")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);

        REQUIRE(board.isSameTeam(Position{2,0}, Position{2,0}));
    }

    SECTION("Check if two Piece is in same Team with one position and one team")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);

        REQUIRE(board.isSameTeam(Position{2,0}, TeamColor::BLUE));
    }

    SECTION("Check if two Piece is NOT in same Team with two position")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);

        REQUIRE(!board.isSameTeam(Position{3,0}, Position{6,0}));
    }

    SECTION("Check if two Piece is NOT in same Team with one position and one team")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        REQUIRE(!board.isSameTeam(Position{3,0}, TeamColor::RED));
    }


    SECTION("Check if position is inside the board")
    {
        Board board{fileTest};
        REQUIRE(board.isInside(Position{3,0}));
    }


    SECTION("Check if position is NOT inside the board")
    {
        Board board{fileTest};
        REQUIRE(!board.isInside(Position{10,0}));
        REQUIRE(!board.isInside(Position{0,10}));
        REQUIRE(!board.isInside(Position{-1,13}));
    }

    SECTION("Check if two piece will fight")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);

        board.movePiece(Position{6,4}, Position{4,4});

        REQUIRE(board.isCombat(Position{4,4}, Position{3,4}));
    }

    SECTION("Check if two piece will NOT fight with different situation")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);

        REQUIRE(!board.isCombat(Position{3,0}, Position{4,0})); // piece vers sol
        REQUIRE(!board.isCombat(Position{2,0}, Position{3,0})); // piece vers un allié
    }


    SECTION("Check if a piece can be put to a specific position")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        board.movePiece(Position{6,4}, Position{4,4});
        REQUIRE(board.canBePut(Position{4,4}, Position{3,4})); // piece vers enemie
        REQUIRE(board.canBePut(Position{6,5}, Position{5,5})); // piece vers sol
    }

    SECTION("Check if a piece can NOT be put to a specific position")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);

        REQUIRE(!board.canBePut(Position{6,5}, Position{7,5})); // piece vers piece allié
        REQUIRE(!board.canBePut(Position{6,3}, Position{5,3})); // piece vers eau
    }
}


TEST_CASE("Movement into the game")
{
    SECTION("Move a piece into a new Position")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        board.movePiece(Position{3,4}, Position{Position{4,4}});
        REQUIRE(board.isCasePiece(Position{4,4}));
        REQUIRE(board.isCaseGround(Position{3,4}));
    }

    SECTION("Get a new Position with a giving direction")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        Position pos{3,4};
        Position newPos = board.newPositionDirection(pos, Direction::BAS);
        REQUIRE((newPos==Position{4,4}));
    }

    SECTION("Fight between two pieces")
    {
        Board board{fileTest};
        board.initializeBoardPlayer(2);
        board.movePiece(Position{6,5}, Position{4,4});
        board.combat(Position{4,4}, Position{3,4});
        REQUIRE_FALSE(board.isCaseGround(Position{3,4}));
        REQUIRE(board.isCaseGround(Position{4,4}));
    }

    SECTION("Fight between one piece and bomb")
        {
            Board board{fileTest};
            board.initializeBoardPlayer(2);
            board.movePiece(Position{6,4}, Position{4,0});
            board.combat(Position{4,0}, Position{3,0});
            REQUIRE(board.isCaseGround(Position{4,0}));
            REQUIRE(board.isCasePiece(Position{3,0}));
        }

    SECTION("Fight between one piece and flag")
        {
            Board board{fileTest};
            board.initializeBoardPlayer(1);
            board.movePiece(Position{9,0}, Position{4,4});
            board.combat(Position{3,4}, Position{4,4});
            REQUIRE(board.isCasePiece(Position{4,4}));
            REQUIRE(board.isCaseGround(Position{3,4}));
        }

}
