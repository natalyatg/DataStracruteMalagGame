#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>


class Exception: public std::exception{};
class DataAlreadyExists: public Exception{};
class DataNotExists: public Exception{};

#endif //EXCEPTIONS_H