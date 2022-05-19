#ifndef VALEURPIECE_H
#define VALEURPIECE_H

#include <stdexcept>

namespace stratego {

    /**
     * @brief The ValeurPiece enum
     *
     * Describe the value of a piece
     *
     */
    enum ValuePiece
    {
        MARECHAL = 10,
        GENERAL = 9,
        COLONEL = 8,
        MAJOR = 7,
        COMMANDANT = 6,
        LIEUTENANT = 5,
        SERGENT = 4,
        DEMINEUR = 3,
        ECLAIREUR = 2,
        ESPIONNE = 1,
        DRAPEAU = 'D',
        BOMBE = 'B'
    };

    /**
     * @brief value_piece_enum
     *
     * Check the value of a piece with his number and
     * Return the value of a piece
     *
     * Throw an exception if the value not exist
     *
     * @param value char : the value of a piece
     * @return value of a piece
     */
    static ValuePiece string_to_value_piece(const std::string &value){
        ValuePiece valPiece;
        if(value=="10"){
            valPiece = ValuePiece::MARECHAL;
        }else if(value=="9"){
            valPiece = ValuePiece::GENERAL;
        }else if(value=="8"){
            valPiece = ValuePiece::COLONEL;
        }else if(value=="7"){
            valPiece = ValuePiece::MAJOR;
        }else if(value=="6"){
            valPiece = ValuePiece::COMMANDANT;
        }else if(value=="5"){
            valPiece = ValuePiece::LIEUTENANT;
        }else if(value=="4"){
            valPiece = ValuePiece::SERGENT;
        }else if(value=="3"){
            valPiece = ValuePiece::DEMINEUR;
        }else if(value=="2"){
            valPiece = ValuePiece::ECLAIREUR;
        }else if(value=="1"){
            valPiece = ValuePiece::ESPIONNE;
        }else if(value=="D"){
            valPiece = ValuePiece::DRAPEAU;
        }else if(value=="B"){
            valPiece = ValuePiece::BOMBE;
        }else{
            throw std::invalid_argument("Aucun des choix existes");
        }
        return valPiece;
    }

    static std::string value_piece_to_string(ValuePiece valPiece){
        switch(valPiece){
        case MARECHAL:
            return "10";
            break;
        case GENERAL:
            return " 9";
            break;
        case COLONEL:
            return " 8";
            break;
        case MAJOR:
            return " 7";
            break;
        case COMMANDANT:
            return " 6";
            break;
        case LIEUTENANT:
            return " 5";
            break;
        case SERGENT:
            return " 4";
            break;
        case DEMINEUR:
            return " 3";
            break;
        case ECLAIREUR:
            return " 2";
            break;
        case ESPIONNE:
            return " 1";
            break;
        case DRAPEAU:
            return " D";
            break;
        case BOMBE:
            return " B";
            break;
        }
    }

}

#endif // VALEURPIECE_H
