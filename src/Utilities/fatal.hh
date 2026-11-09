// -----------------------------------------------------------------------
// fatal.hh: single point of failure handling for the BBarolo library.
//
// By default BBarolo terminates the process on unrecoverable errors, which
// is the expected behaviour for the command-line tool. Applications that
// embed libbbarolo (e.g. SlicerAstro) can compile it with
// BBAROLO_THROW_ON_ERROR defined: errors are then reported by throwing
// bbarolo::Error, so the host application can recover.
// -----------------------------------------------------------------------

#ifndef FATAL_HH_
#define FATAL_HH_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>

namespace bbarolo {

class Error : public std::runtime_error {
public:
    explicit Error(const std::string &what) : std::runtime_error(what) {}
};

[[noreturn]] inline void fatal(const char *where = "BBarolo fatal error") {
#ifdef BBAROLO_THROW_ON_ERROR
    throw Error(where);
#else
    (void)where;
    std::terminate();
#endif
}

} // namespace bbarolo

#define BBAROLO_FATAL() bbarolo::fatal(__FILE__ ":" BBAROLO_STRINGIFY(__LINE__))
#define BBAROLO_STRINGIFY(x) BBAROLO_STRINGIFY_(x)
#define BBAROLO_STRINGIFY_(x) #x

#endif
