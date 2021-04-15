//
// Created by student on 12.01.2020.
//

#include "../../include/exceptions/ClientExceptions.h"

using namespace std;

ClientException::ClientException(const std::string &message) : logic_error(message) {}

std::string ClientException::message() const {
    return what();
}

ClientConstructionException::ClientConstructionException(const std::string &message) : ClientException(message) {}

ClientModificationException::ClientModificationException(const std::string &message) : ClientException(message) {}

ClientTypeException::ClientTypeException(const std::string &message) : ClientException(message) {}

ClientTypeConstructionException::ClientTypeConstructionException(const std::string &message) : ClientTypeException(message) {}

ClientTypeModificationException::ClientTypeModificationException(const std::string &message) : ClientTypeException(message) {}

ClientTypeMethodException::ClientTypeMethodException(const std::string &message) : ClientTypeException(message) {}

ClientRepositoryException::ClientRepositoryException(const std::string &message) : ClientException(message) {}

ClientBuilderException::ClientBuilderException(const std::string &message) : ClientException(message) {}

ClientBuilderModificationException::ClientBuilderModificationException(const std::string &message) : ClientBuilderException(message) {}

ClientBuilderBuildException::ClientBuilderBuildException(const std::string &message) : ClientBuilderException(message) {}

ClientManagerException::ClientManagerException(const std::string &message) : ClientException(message) {}

ClientManagerConstructionException::ClientManagerConstructionException(const std::string &message) : ClientManagerException(message) {}

ClientManagerMethodException::ClientManagerMethodException(const std::string &message) : ClientManagerException(message) {}
