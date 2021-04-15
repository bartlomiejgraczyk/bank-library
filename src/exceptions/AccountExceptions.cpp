//
// Created by student on 12.01.2020.
//

#include "exceptions/AccountExceptions.h"

using namespace std;

AccountException::AccountException(const std::string &message) : logic_error(message) {}

std::string AccountException::message() const {
    return what();
}

AccountConstructionException::AccountConstructionException(const std::string &message) : AccountException(message) {}

AccountModificationException::AccountModificationException(const std::string &message) : AccountException(message) {}

AccountMethodException::AccountMethodException(const std::string &message) : AccountException(message) {}

JointAccountException::JointAccountException(const std::string &message) : AccountException(message) {}

JointAccountConstructionException::JointAccountConstructionException(const std::string &message) : JointAccountException(message) {}

JointAccountMethodException::JointAccountMethodException(const std::string &message) : JointAccountException(message) {}

AccountRepositoryException::AccountRepositoryException(const std::string &message) : AccountException(message) {}

AccountBuilderException::AccountBuilderException(const std::string &message) : AccountException(message) {}

AccountBuilderModificationException::AccountBuilderModificationException(const std::string &message) : AccountBuilderException(message) {}

AccountBuilderBuildException::AccountBuilderBuildException(const std::string &message) : AccountBuilderException(message) {}

AccountManagerException::AccountManagerException(const std::string &message) : AccountException(message) {}

AccountManagerConstructionException::AccountManagerConstructionException(const std::string &message) : AccountManagerException(message) {}

AccountManagerMethodException::AccountManagerMethodException(const std::string &message) : AccountManagerException(message) {}