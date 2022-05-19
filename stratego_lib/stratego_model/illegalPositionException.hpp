#ifndef ILLEGALPOSITIONEXCEPTION_HPP
#define ILLEGALPOSITIONEXCEPTION_HPP

#include <iostream>
#include "strategoException.hpp"

namespace stratego {
    namespace exception {

    /**
     * @brief The IllegalPositionException class, a customized exception class that inherit the methods and attributes of StrategoException.
     */
    class IllegalPositionException: public StrategoException {
    public:

        /**
         * @brief IllegalPositionException a simple constructor of the IllegalPositionException class.
         *
         * @param msg a string.
         * @param fileName a string.
         * @param functionName a string.
         * @param line an integer.
         */
        inline IllegalPositionException(const std::string&  msg, const std::string & fileName, const std::string &functionName, const int line):StrategoException(msg, fileName, functionName, line)
        {}
    };

    }

}


#endif // ILLEGALPOSITIONEXCEPTION_HPP
