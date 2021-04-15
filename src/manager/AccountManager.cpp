//
// Created by student on 21.12.2019.
//

#include <utility>

#include "manager/AccountManager.h"
#include "repository/AccountRepository.h"

using namespace std;

AccountManager::AccountManager(AccountRepositorySPtr closedAccounts, AccountRepositorySPtr jointAccounts, AccountRepositorySPtr savingsAccounts, AccountRepositorySPtr currencyAccounts)
        : closedAccounts(move(closedAccounts)), jointAccounts(move(jointAccounts)), savingsAccounts(move(savingsAccounts)), currencyAccounts(move(currencyAccounts)) {}

AccountManager::~AccountManager() = default;
