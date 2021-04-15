//
// Created by student on 12.01.2020.
//

#include "exceptions/CardExceptions.h"

using namespace std;

CardException::CardException(const std::string &message) : logic_error(message) {}

std::string CardException::message() const {
    return what();
}

CardConstructionException::CardConstructionException(const std::string &message) : CardException(message) {}

CardModificationException::CardModificationException(const std::string &message) : CardException(message) {}

CardMethodException::CardMethodException(const std::string &message) : CardException(message) {}

CardClassException::CardClassException(const std::string &message) : CardException(message) {}

CardClassConstructionException::CardClassConstructionException(const std::string &message) : CardClassException(message) {}

CardClassMethodException::CardClassMethodException(const std::string &message) : CardClassException(message) {}

CardRepositoryException::CardRepositoryException(const std::string &message) : CardException(message) {}

CardBuilderException::CardBuilderException(const std::string &message) : CardException(message) {}

CardBuilderModificationException::CardBuilderModificationException(const std::string &message) : CardBuilderException(message) {}

CardBuilderBuildException::CardBuilderBuildException(const std::string &message) : CardBuilderException(message) {}

CardManagerException::CardManagerException(const std::string &message) : CardException(message) {}

CardManagerConstructionException::CardManagerConstructionException(const std::string &message) : CardManagerException(message) {}

CardManagerMethodException::CardManagerMethodException(const std::string &message) : CardManagerException(message) {}