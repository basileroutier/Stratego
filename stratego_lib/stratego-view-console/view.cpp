#include "view.h"
#include <iostream>
#include <cctype>
#include "direction.h"
#include<limits>

using namespace std;


namespace stratego {
    View::View(Game & model):
        model_{model}{}

    Direction value_to_direction(char direction){
        switch(direction){
            case 'H':
                return Direction::HAUT;
                break;
            case 'B':
                return Direction::BAS;
                break;
            case 'G':
                return Direction::GAUCHE;
                break;
            case 'D':
                return Direction::DROITE;
                break;
            default:
                return Direction::NOT_VALID;
        }
    }

    Position View::askPiecePosition() const{
        int positionX = verifInt("Entrez la ligne pour choisir votre piece à déplacer : ", 0, (model_.getBoard().row_)-1);
        int positionY = verifInt("Entrez la colonne pour choisir votre piece à déplacer : ", 0, (model_.getBoard().row_)-1);
        Position positionChoice{positionX, positionY};

        while(!model_.canBeSelected(positionChoice)){
            displayError("La position n'est pas possible à selectionner");
            positionX = verifInt("Entrez la ligne pour choisir votre piece à déplacer : ", 0,model_.getBoard().row_-1);
            positionY = verifInt("Entrez la colonne pour choisir votre piece à déplacer : ", 0,model_.getBoard().row_-1);
            positionChoice = {positionX, positionY};
        }

        return positionChoice;
    }

    Direction View::askDirection() const{
        string messageInput = "Entrer une direction : \n 'H' pour haut, \n 'B' pour bas, \n 'G' pour gauche, \n 'D' pour droite. \n -> :";
        string input= verifString(messageInput);
        char dir = input[0];
        dir = toupper(dir);

        Direction direction = value_to_direction(dir);

        while(direction==Direction::NOT_VALID || !model_.canBeMove(direction)){
            displayError("La direction n'existe pas ou bien celle-ci n'est pas correct car le pion ne peut pas être déplacé");
            input= verifString(messageInput);
            dir = input[0];
            dir = toupper(dir);
            direction = value_to_direction(dir);
        }

        return direction;
    }

    int View::askNumberOfMove(Direction direction) const{
        string messageInput = "De combien de cases voulez-vous avancer ?";
        int numberMove = verifInt(messageInput, 1 ,(model_.getBoard().row_)-1 );
        while(!model_.canBeMoveForEclaireur(direction, numberMove)){
            displayError("Le nombre d'erreur n'est pas correct, car il rencontre soit de l'eau, soit un pion avant sa position de fin");
            numberMove = verifInt(messageInput, 1 ,(model_.getBoard().row_)-1 );
        }
        return numberMove;
    }



    void View::displayBoard(const string &boardStr) const{
        cout << boardStr <<endl;
    }

    int View::askNumberOfFile() const{
        string messageInput = "Entrer le nombre de fichier. Si vous choisissez 1, alors les deux joueurs auront le meme fichier.\n\tSi 2, alors le joueur 1 aura le premier fichier et le joueur 2 le deuxieme";
        int numberFile = verifInt(messageInput, 1, 2);
        return numberFile;
    }

    void View::displayCombat(Piece piece1, Piece piece2) const{
        cout << endl;
        cout << " ----------  Un combat est lance entre deux pieces  ----------" << endl << endl;

        cout << "Votre piece choisie :  "<< value_piece_to_string(piece1.valuePiece()) << endl;
        cout << "La piece de l'adversaire :  " << value_piece_to_string(piece2.valuePiece()) << endl;

        if(piece1>piece2){
            cout << "Vous avez battu la piece "<< piece2.team() <<"."<< "Avance en toute discretion." << endl;
        }else if(piece2 > piece1){
            cout << "Vous vous etes attaque a plus fort que vous. Vous avez perdu votre pion." << endl;
        }else{
            cout << "Vous vous etes enfourche l'un dans l'autre en ayant les memes defenses." << endl;
        }
        cout << endl<<"----------------  Fin du combat  ----------------" << endl << endl;

    }

    void View::displayEndGame() const
    {
        cout << "Vous etes arrive a la fin du jeu." << endl;
        cout << "Le gagant est...." << endl<<endl;
        displayWinner(model_.getWinner());
    }

    void View::displayWinner(TeamColor winner) const{
        switch(winner){
            case BLUE:
                cout << "le BLEU " << endl;
                break;
            case RED:
                 cout << "le ROUGE " << endl;
                break;
            case NONE:
                 cout << " AUCUN, c'est une égalité UwU" << endl;
                break;
        }


    }

    void View::displayError(const string &error) const{
        cout <<"--------------------------------" << endl;
        cout << "   " << error << endl;
        cout <<"--------------------------------" << endl;
    }

    int View::verifInt(const string &message, int start, int end) const{
        int entier;
        cout << message << endl;
        while ( ! ( cin >> entier ) || entier < start || entier > end ){
            if ( cin.fail() ){
                cout << "Saisie incorrecte, recommencez : " <<endl;
                cout << message << endl;
                cin.clear();
                cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
             }else{
                cout << "Le chiffre n'est pas entre " << to_string(start) << " et " << to_string(end) << endl;
             }
       }
        return entier;
    }

    string View::verifString(const string& message) const
    {
        string chaine;
        cout << message << endl;

        while ( ! ( cin >> chaine )){
            if ( cin.fail() ){
                cout << "Saisie incorrecte, recommencez : " <<endl;
                cout << message << endl;
                cin.clear();
                cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
             }
       }

        return chaine;
    }

    bool View::askDebugMode() const{
        cout << "voulez-vous jouer en debug mode ? (Y | N)" <<endl;
        char c;
        cin >> c;
        c = toupper(c);
        if(c == 'Y'){
            return true;
        }
        return false;
    }

    void View::displayTeamTurn(TeamColor team) const
    {
        if(team == 'R'){
            cout << "C'est au tour de l'équipe rouge de jouer." <<endl;
        }
        else{
            cout << "C'est au tour de l'équipe bleue de jouer." <<endl;
        }
    }


}
