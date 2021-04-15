//
// Created by student on 13.01.2020.
//

#include "exceptions/AddressExceptions.h"

using namespace std;

AddressException::AddressException(const std::string &message) : logic_error(message) {}

std::string AddressException::message() const {
    return what();
}
