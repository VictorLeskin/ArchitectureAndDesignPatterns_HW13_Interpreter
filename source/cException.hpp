///************************* OUTS HOMEWORK ****************************************
#ifndef CEXCEPTION_HPP
#define CEXCEPTION_HPP

#include <stdexcept>

// base class of exception used in task. Just keep a text of a event.
class cException : public std::exception
{
public:
    cException(const char* sz) : szWhat(sz) {}

    const char* what() const noexcept { return szWhat; }

protected:
    const char* szWhat;
};


#endif //#ifndef CEXCEPTION_HPP
