#ifndef ILLEGALDIRECTIONEXCEPTION_H
#define ILLEGALDIRECTIONEXCEPTION_H


#include <iostream>
#include "strategoException.hpp"

namespace stratego {
namespace exception {

/**
 * @brief The virtual DirectionException class, a customized exception class that inherit the methods and attributes of StrategoException.
 */
class IllegalDirectionException: public StrategoException{
public:

    /**
     * @brief DirectionException a simple constructor of the virtual DirectionException class.
     *
     * @param msg a string.
     * @param fileName a string.
     * @param functionName a string.
     * @param line an integer.
     */
    inline IllegalDirectionException(const std::string&  msg, const std::string & fileName, const std::string &functionName, const int line):StrategoException(msg, fileName, functionName, line)
    {}
};
}

} // namespace stratego::exception

#endif // ILLEGALDIRECTIONEXCEPTION_H
