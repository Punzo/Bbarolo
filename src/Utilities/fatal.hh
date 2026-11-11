// -----------------------------------------------------------------------
// fatal.hh: single point of failure handling for the BBarolo library.
//
// By default BBarolo terminates the process on unrecoverable errors, which
// is the expected behaviour for the command-line tool. Applications that
// embed libbbarolo (e.g. SlicerAstro) can compile it with
// BBAROLO_THROW_ON_ERROR defined: errors are then reported by throwing
// bbarolo::Error, which carries the error message, so the host application
// can report it and recover.
//
// The message is always written to std::cerr as well (as BBarolo did
// before), so the command-line output is unchanged.
// -----------------------------------------------------------------------

#ifndef FATAL_HH_
#define FATAL_HH_

#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace bbarolo {

class Error : public std::runtime_error {
public:
    explicit Error(const std::string &what) : std::runtime_error(what) {}
};

/// Report an unrecoverable error: the message is written to std::cerr,
/// then bbarolo::Error is thrown (BBAROLO_THROW_ON_ERROR) or the process
/// is terminated.
[[noreturn]] inline void fatal(const std::string &message, const char *where) {
    std::string text(message);
    // single line, without the decorations of the console messages
    const std::string spaces = " \t\r\n";
    std::string::size_type first = text.find_first_not_of(spaces);
    std::string::size_type last = text.find_last_not_of(spaces);
    text = first == std::string::npos ? std::string("unknown error") : text.substr(first, last - first + 1);
    for (std::string::size_type i = 0; i < text.size(); i++) {
        if (text[i] == '\n' || text[i] == '\r') text[i] = ' ';
    }
    std::cerr << message << std::endl;
#ifdef BBAROLO_THROW_ON_ERROR
    throw Error(text + " [" + where + "]");
#else
    (void)where;
    std::terminate();
#endif
}

} // namespace bbarolo

#define BBAROLO_STRINGIFY_(x) #x
#define BBAROLO_STRINGIFY(x) BBAROLO_STRINGIFY_(x)

/// Unrecoverable error with a message built with the stream operator, e.g.
/// BBAROLO_FATAL_MSG("3DFIT ERROR: Negative radius " << radius);
#define BBAROLO_FATAL_MSG(...)                                                  \
    do {                                                                        \
        std::ostringstream bbaroloFatalStream;                                  \
        bbaroloFatalStream << __VA_ARGS__;                                      \
        bbarolo::fatal(bbaroloFatalStream.str(),                                \
                       __FILE__ ":" BBAROLO_STRINGIFY(__LINE__));               \
    } while (0)

#endif
