#ifndef __INVALID_MOVE_EXCEPTION
#define __INVALID_MOVE_EXCEPTION

#include <exception>

class InvalidMoveException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "An invalid move was made";
  }
} invalidMoveException;

#endif