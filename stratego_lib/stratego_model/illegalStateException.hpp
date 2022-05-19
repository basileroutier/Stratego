#ifndef ILLEGALSTATEEXCEPTION_H
#define ILLEGALSTATEEXCEPTION_H


#include <iostream>
#include "strategoException.hpp"

namespace stratego {

namespace exception {

/**
 * @brief The IllegalStateException class, a customized exception class that inherit the methods and attributes of StrategoException.
 */
class IllegalStateException: public StrategoException {
public:

    /**
     * @brief IllegalStateException a simple constructor of the IllegalStateException class.
     *
     * @param msg a string.
     * @param fileName a string.
     * @param functionName a string.
     * @param line an integer.
     */
    inline IllegalStateException(const std::string&  msg, const std::string & fileName, const std::string &functionName, const int line):StrategoException(msg, fileName, functionName, line)
    {}
};
}

}

#endif // ILLEGALSTATEEXCEPTION_H
