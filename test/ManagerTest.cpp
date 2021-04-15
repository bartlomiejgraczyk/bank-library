//
// Created by student on 11.01.2020.
//

#include <boost/test/unit_test.hpp>
#include <boost/date_time/local_time/local_time.hpp>

#include "repository/ClientRepository.h"
#include "repository/LoanRepository.h"
#include "manager/ClientManager.h"
#include "manager/LoanManager.h"
#include "builder/LoanBuilder.h"
#include "model/Client.h"
#include "model/Card.h"
#include "model/Loan.h"
#include "model/Account.h"
#include "model/Address.h"
#include "model/Amount.h"
#include "model/ClientType.h"
#include "model/StandardLoan.h"
#include "enum/LoanRepositoriesEnum.h"
#include "exceptions/ClientExceptions.h"
#include "exceptions/AccountExceptions.h"
#include "exceptions/LoanExceptions.h"
#include "exceptions/CardExceptions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(TestSuiteCorrectManager)

    BOOST_AUTO_TEST_CASE(ClientManagerFunctionalityTest) {
        BOOST_TEST_MESSAGE("Beginning of ClientManagerFunctionalityTest:");

        ClientSPtr client1(new Client("John", "Kowalski", "23543234", AddressUPtr(new Address("Piotrkowska", "1"))));

        ClientRepositorySPtr standardClients(new ClientRepository());
        ClientRepositorySPtr formerClients(new ClientRepository());
        ClientRepositorySPtr debtors(new ClientRepository());

        ClientManagerUPtr clientManager(new ClientManager(formerClients, debtors, standardClients));

        BOOST_CHECK_THROW(ClientManager(nullptr, debtors, standardClients), ClientManagerConstructionException);
        BOOST_CHECK_THROW(ClientManager(formerClients, nullptr, standardClients), ClientManagerConstructionException);
        BOOST_CHECK_THROW(ClientManager(formerClients, debtors, nullptr), ClientManagerConstructionException);

        BOOST_CHECK_THROW(clientManager->clientInfo(nullptr), ClientManagerMethodException);
        BOOST_CHECK_THROW(clientManager->changeClientStatus(nullptr, StandardClientsRepo), ClientManagerMethodException);
        BOOST_CHECK_THROW(clientManager->changeClientStatus(client1, StandardClientsRepo), ClientManagerMethodException);

        BOOST_CHECK_NO_THROW(clientManager->addClient(client1, StandardClientsRepo));
        BOOST_CHECK_THROW(clientManager->addClient(client1, StandardClientsRepo), ClientManagerException);
        BOOST_CHECK_NO_THROW(clientManager->changeClientStatus(client1, DebtorsRepo));
        BOOST_CHECK_NO_THROW(clientManager->clientInfo(client1));
        BOOST_TEST_MESSAGE(clientManager->clientInfo(client1));
        BOOST_CHECK_EQUAL(clientManager->getClient([](const ClientSPtr &repoClient) { return repoClient->getPersonalID() == "23543234"; }, DebtorsRepo), client1);
        BOOST_CHECK_EQUAL(clientManager->getClient([](const ClientSPtr &repoClient) { return repoClient->getPersonalID() == "3"; }, DebtorsRepo), nullptr);

        BOOST_TEST_MESSAGE("End of ClientManagerFunctionalityTest");
    }

    BOOST_AUTO_TEST_CASE(AccountManagerFunctionalityTest) {
        BOOST_TEST_MESSAGE("Beginning of AccountManagerFunctionalityTest:");

        BOOST_TEST_MESSAGE("End of AccountManagerFunctionalityTest");
    }

    BOOST_AUTO_TEST_CASE(CardManagerFunctionalityTest) {
        BOOST_TEST_MESSAGE("Beginning of CardManagerFunctionalityTest:");

        BOOST_TEST_MESSAGE("End of CardManagerFunctionalityTest");
    }

    BOOST_AUTO_TEST_CASE(LoanManagerFunctionalityTest) {
        BOOST_TEST_MESSAGE("Beginning of LoanManagerFunctionalityTest:");

        LoanRepositorySPtr currentLoans(new LoanRepository());
        LoanRepositorySPtr finalizedLoans(new LoanRepository());

        LoanManagerUPtr loanManager(new LoanManager(currentLoans, finalizedLoans));

        BOOST_CHECK_THROW(LoanManager(nullptr, finalizedLoans), LoanManagerConstructionException);
        BOOST_CHECK_THROW(LoanManager(currentLoans, nullptr), LoanManagerConstructionException);

        boost::local_time::time_zone_ptr zone(new boost::local_time::posix_time_zone("CET"));
        boost::posix_time::ptime time = boost::posix_time::second_clock::local_time();
        shared_ptr<boost::local_time::local_date_time> time1(new boost::local_time::local_date_time(time, zone));
        unique_ptr<boost::local_time::local_date_time> time2(new boost::local_time::local_date_time(time, zone));

        ClientSPtr client1(new Client("John", "Kowalski", "23543234", AddressUPtr(new Address("Piotrkowska", "1"))));
        LoanBuilderSPtr loanBuilder(new LoanBuilder());

        loanBuilder = loanBuilder->setBorrower(client1)
                ->setLoanType(make_shared<LoanEnum>(StandardLoanType))
                ->setBorrowDate(time1)
                ->setBorrowedAmount(make_shared<Amount>(Amount(3000L, 0, PLN)));

        BOOST_CHECK_THROW(loanManager->createLoan(nullptr), LoanManagerMethodException);
        BOOST_CHECK_THROW(loanManager->createLoan(make_shared<LoanBuilder>(LoanBuilder())), LoanManagerException);
        BOOST_CHECK_THROW(loanManager->createLoan(nullptr), LoanManagerMethodException);
        BOOST_CHECK_THROW(loanManager->createLoan(loanBuilder), LoanManagerMethodException);

        client1->getClientType()->setBaseServiceTier(0);

        loanBuilder = loanBuilder->setBorrower(client1)
                ->setLoanType(make_shared<LoanEnum>(StandardLoanType))
                ->setBorrowDate(time1)
                ->setBorrowedAmount(make_shared<Amount>(Amount(10L, 0, PLN)));

        BOOST_CHECK_THROW(loanManager->createLoan(loanBuilder), LoanManagerMethodException);

        client1->getClientType()->setBaseServiceTier(20);

        loanBuilder = loanBuilder->setBorrower(client1)
                ->setLoanType(make_shared<LoanEnum>(StandardLoanType))
                ->setBorrowDate(time1)
                ->setBorrowedAmount(make_shared<Amount>(Amount(10L, 0, PLN)));

        BOOST_CHECK_NO_THROW(loanManager->createLoan(loanBuilder));
        BOOST_CHECK_EQUAL(client1->getCreditworthiness(), 10);
        BOOST_CHECK_EQUAL(client1->getNumberOfLoans(), 1);
        BOOST_CHECK_EQUAL(currentLoans->getAll().size(), 1);

        LoanSPtr loan = loanManager->getLoan([&client1](const LoanSPtr &currentLoan) { return currentLoan->getBorrower() == client1; }, CurrentLoansType);
        LoanSPtr loan2(new StandardLoan(move(time2), AmountUPtr(new Amount(40L, 0, PLN)), client1));

        BOOST_CHECK_THROW(loanManager->returnMoney(nullptr, make_shared<Amount>(Amount(10L, 0, PLN))), LoanManagerMethodException);
        BOOST_CHECK_THROW(loanManager->returnMoney(loan2, make_shared<Amount>(Amount(10L, 0, PLN))), LoanManagerMethodException);
        BOOST_CHECK_NO_THROW(loanManager->returnMoney(loan, make_shared<Amount>(Amount(12L, 0, PLN))));
        BOOST_CHECK_THROW(loanManager->returnMoney(loan, make_shared<Amount>(Amount(12L, 0, PLN))), LoanManagerMethodException);


        loanBuilder = loanBuilder->setBorrower(client1)
                ->setLoanType(make_shared<LoanEnum>(StandardLoanType))
                ->setBorrowDate(time1)
                ->setBorrowedAmount(make_shared<Amount>(Amount(10L, 0, PLN)));

        BOOST_CHECK_NO_THROW(loanManager->createLoan(loanBuilder));
        BOOST_CHECK_EQUAL(client1->getCreditworthiness(), 22);
        BOOST_CHECK_EQUAL(client1->getNumberOfLoans(), 1);
        BOOST_CHECK_EQUAL(currentLoans->getAll().size(), 1);
        BOOST_CHECK_EQUAL(finalizedLoans->getAll().size(), 1);

        loanBuilder = loanBuilder->setBorrower(client1)
                ->setLoanType(make_shared<LoanEnum>(StandardLoanType))
                ->setBorrowDate(time1)
                ->setBorrowedAmount(make_shared<Amount>(Amount(30L, 0, PLN)));

        BOOST_CHECK_NO_THROW(loanManager->createLoan(loanBuilder));
        BOOST_CHECK_EQUAL(client1->getCreditworthiness(), 17);
        BOOST_CHECK(*client1->getFounds()[PLN] < Amount(0L, 0, PLN));

        BOOST_CHECK_THROW(loanManager->loanInfo(nullptr), LoanManagerMethodException);
        BOOST_TEST_MESSAGE(loanManager->loanInfo(loan));

        LoanSPtr loan3 = loanManager->getLoan([](const LoanSPtr &currentLoan) { return currentLoan->getBorrowedAmount()->getMainUnit() == 30L; }, CurrentLoansType);

        BOOST_CHECK_THROW(loanManager->markAsFinalized(nullptr), LoanManagerMethodException);
        BOOST_CHECK_THROW(loanManager->markAsFinalized(loan2), LoanManagerMethodException);
        BOOST_CHECK_THROW(loanManager->markAsFinalized(nullptr), LoanManagerMethodException);
        BOOST_CHECK_NO_THROW(loanManager->markAsFinalized(loan3));

        BOOST_CHECK_EQUAL(client1->getNumberOfLoans(), 1);
        BOOST_CHECK_EQUAL(currentLoans->getAll().size(), 1);

        BOOST_TEST_MESSAGE("End of LoanManagerFunctionalityTest");
    }

BOOST_AUTO_TEST_SUITE_END()