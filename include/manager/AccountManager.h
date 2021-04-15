//
// Created by student on 21.12.2019.
//

#ifndef BANKKONTA_ACCOUNTMANAGER_H
#define BANKKONTA_ACCOUNTMANAGER_H


#include <memory>
#include <functional>

class Client;

class Amount;

class Account;

class AccountRepository;

class AccountManager {
private:
    std::shared_ptr<AccountRepository> closedAccounts;
    std::shared_ptr<AccountRepository> jointAccounts;
    std::shared_ptr<AccountRepository> savingsAccounts;
    std::shared_ptr<AccountRepository> currencyAccounts;

public:
    AccountManager(std::shared_ptr<AccountRepository> closedAccounts,
                   std::shared_ptr<AccountRepository> jointAccounts,
                   std::shared_ptr<AccountRepository> savingsAccounts,
                   std::shared_ptr<AccountRepository> currencyAccounts);

    virtual ~AccountManager();

    void closeAccount(std::shared_ptr<Account> account);

    void addAccount(std::shared_ptr<Account> account);

    std::shared_ptr<Account> getAccount(std::function<bool(std::shared_ptr<Account> account)> predicate);

    void makeTransfer(std::shared_ptr<Account> from, std::shared_ptr<Account> to, std::shared_ptr<Amount> amount);

    void addOwnerToAccount(std::shared_ptr<Account> account, std::shared_ptr<Client> owner);

    void removeOwnerFromAccount(std::shared_ptr<Account> account, std::shared_ptr<Client> owner);

    std::string accountInfo(std::shared_ptr<Account> account) const;
};

typedef std::shared_ptr<AccountManager> AccountManagerSPtr;
typedef std::unique_ptr<AccountManager> AccountManagerUPtr;

#endif //BANKKONTA_ACCOUNTMANAGER_H
