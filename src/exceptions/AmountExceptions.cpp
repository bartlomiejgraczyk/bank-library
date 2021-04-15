//
// Created by student on 13.01.2020.
//

#include "exceptions/AmountExceptions.h"

AmountException::AmountException(const std::string &message) : logic_error(message) {}

std::string AmountException::message() const {
    return what();
}

AmountConstructionException::AmountConstructionException(const std::string &message) : AmountException(message) {}

AmountOperatorException::AmountOperatorException(const std::string &message) : AmountException(message) {}
