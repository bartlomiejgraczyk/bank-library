//
// Created by student on 21.12.2019.
//

#ifndef BANKKONTA_CARDMANAGER_H
#define BANKKONTA_CARDMANAGER_H


#include <vector>
#include <memory>
#include <functional>

class Amount;

class Card;

class CardRepository;

class CardManager {
private:
    std::shared_ptr<CardRepository> lostCards;
    std::shared_ptr<CardRepository> canceledCards;
    std::shared_ptr<CardRepository> creditCards;
    std::shared_ptr<CardRepository> debitCards;

public:
    CardManager(std::shared_ptr<CardRepository> lostCards, std::shared_ptr<CardRepository> canceledCards, std::shared_ptr<CardRepository> creditCards, std::shared_ptr<CardRepository> debitCards);

    virtual ~CardManager();

    void addCard(std::shared_ptr<Card> card);

    std::shared_ptr<Card> getCard(std::function<bool(std::shared_ptr<Card>)> predicate);

    void markCardAsLost(std::shared_ptr<Card> card);

    void cancelCard(std::shared_ptr<Card> card);

    void withdrawMoney(std::shared_ptr<Card> card, std::shared_ptr<Amount> amount);

    void makePayment(std::shared_ptr<Card> card, std::shared_ptr<Amount> amount);

    void payBack(std::shared_ptr<Card> card, std::shared_ptr<Amount> amount);

    std::string cardInfo(std::shared_ptr<Card> card) const;

};

typedef std::shared_ptr<CardManager> CardManagerSPtr;
typedef std::unique_ptr<CardManager> CardManagerUPtr;

#endif //BANKKONTA_CARDMANAGER_H
