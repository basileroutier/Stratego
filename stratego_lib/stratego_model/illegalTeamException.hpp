#ifndef ILLEGALTEAMEXCEPTION_HPP
#define ILLEGALTEAMEXCEPTION_HPP


#include <iostream>
#include "strategoException.hpp"

namespace stratego {

namespace exception {

/**
 * @brief The IllegalTeamException class, a customized exception class that inherit the methods and attributes of StrategoException.
 */
class IllegalTeamException: public StrategoException {
public:

    /**
     * @brief IllegalTeamException a simple constructor of the IllegalTeamException class.
     *
     * @param msg a string.
     * @param fileName a string.
     * @param functionName a string.
     * @param line an integer.
     */
    inline IllegalTeamException(const std::string&  msg, const std::string & fileName, const std::string &functionName, const int line):StrategoException(msg, fileName, functionName, line)
    {}
};
}

}

#endif // ILLEGALTEAMEXCEPTION_HPP
