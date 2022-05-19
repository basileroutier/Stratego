#ifndef TERMINALCOLOR_H
#define TERMINALCOLOR_H

#include <string>

/**
 * @brief The TerminalColor to write in color in terminal.
 * So beautifull struct.
 *
 * @author pbt - Pierre Bettens pbettens@he2b.be
 */
namespace stratego {
struct TerminalColor {
    inline static const std::string DEFAULT = "\033[0m";
    inline static const std::string RED = "<ESC>[31m";	 //"\033[31m";
    inline static const std::string GREEN = "\033[32m";
    inline static const std::string BLACK = "\033[30m";
    inline static const std::string YELLOW = "\033[33m";
    inline static const std::string BLUE = "\033[34m";
    inline static const std::string MAGENTA = "\033[35m";
    inline static const std::string CYAN = "\033[36m";
    inline static const std::string WHITE = "\033[38m";
    inline static const std::string LIGHT_GREY = "\033[37m";
    inline static const std::string DARK_GREY = "\033[90m";
    inline static const std::string LIGHT_RED = "\033[91m";
};
}
#endif // TERMINALCOLOR_H
