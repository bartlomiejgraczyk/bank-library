//
// Created by student on 12.01.2020.
//

#include "exceptions/LoanExceptions.h"

using namespace std;

LoanException::LoanException(const std::string &message) : logic_error(message) {}

std::string LoanException::message() const {
    return what();
}

LoanConstructionException::LoanConstructionException(const std::string &message) : LoanException(message) {}

LoanModificationException::LoanModificationException(const std::string &message) : LoanException(message) {}

ConsolidationLoanException::ConsolidationLoanException(const std::string &message) : LoanException(message) {}

ConsolidationLoanConstructionException::ConsolidationLoanConstructionException(const std::string &message) : ConsolidationLoanException(message) {}

ConsolidationLoanMethodException::ConsolidationLoanMethodException(const std::string &message) : ConsolidationLoanException(message) {}

LoanRepositoryException::LoanRepositoryException(const std::string &message) : LoanException(message) {}

LoanBuilderException::LoanBuilderException(const std::string &message) : LoanException(message) {}

LoanBuilderModificationException::LoanBuilderModificationException(const std::string &message) : LoanBuilderException(message) {}

LoanBuilderBuildException::LoanBuilderBuildException(const std::string &message) : LoanBuilderException(message) {}

LoanManagerException::LoanManagerException(const std::string &message) : LoanException(message) {}

LoanManagerConstructionException::LoanManagerConstructionException(const std::string &message) : LoanManagerException(message) {}

LoanManagerMethodException::LoanManagerMethodException(const std::string &message) : LoanManagerException(message) {}
