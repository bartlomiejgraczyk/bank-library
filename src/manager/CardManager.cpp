//
// Created by student on 21.12.2019.
//

#include <utility>

#include "manager/CardManager.h"
#include "repository/CardRepository.h"

using namespace std;

CardManager::CardManager(CardRepositorySPtr lostCards, CardRepositorySPtr canceledCards, CardRepositorySPtr creditCards, CardRepositorySPtr debitCards)
        : lostCards(move(lostCards)), canceledCards(move(canceledCards)), creditCards(move(creditCards)), debitCards(move(debitCards)) {}

CardManager::~CardManager() = default;
