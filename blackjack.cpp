#ifndef BLACKJACK
#define BLACKJACK

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <numeric>
#include <cstdlib>

#include <raylib.h>
#include "include/blackjack.h"
#include "include/card.h"
#include "include/app.h"

Player::Player(std::string pname) {
    name = pname;
};

std::string Player::GetPlayerName() {
    return name;
};

bool Player::Hit() {
    Card* card = House::GetCard();
    deck.push_back(card);
    return true;
};
int Player::GetDeckSum() {
    int sum = 0;
    for (Card* card : deck) {
        sum += card->GetGameValue();
    }
    return sum;
};
std::vector<Card*> Player::GetDeck() {
    return deck;
};
void Player::ResetDeck() {
    deck = {};
};
void Player::SetBalance(int newbalance) {
    balance = newbalance;
}
int Player::GetBalance() {
    return balance;
}
void Player::AddBalance(int newbalance) {
    balance += newbalance;
}
void Player::SetBet(int newbet) {
    bet = newbet;
}
int Player::GetBet() {
    return bet;
}

void Player::DrawCards(std::vector<Texture2D> textures, std::pair<int, int> position, std::pair<int, int> offset) {
    int cardWidth = deck[0]->GetSize().first;
    int tableWidth = cardWidth * deck.size() + offset.first * (deck.size() - 1);
    int xpos = (position.first - tableWidth/2) + cardWidth / 2;
    int ypos = position.second;//deck[0]->GetPos().second;
    for (Card* card : deck) {
        card->SetPos({xpos, ypos});
        card->Draw(textures);
        xpos += offset.first + deck[0]->GetSize().first;
        ypos += offset.second;
    }
};

// House
std::vector<Card*> House::deck;
void House::GenerateDeck() {
    House::deck = {};
    for (int value = 1; value < 14; value++) {
        for (int symbol = 1; symbol < 5; symbol++) {
            Card* card = new Card({SCREENSIZE.first/2, SCREENSIZE.second/2}, {0, 0}, {64, 128});
            card->SetValue(value);
            card->SetGameValue(value);
            if (value > 10) card->SetGameValue(10); // Faces are 10
            if (value == 1) card->SetGameValue(11); // Ace is 11
            card->SetSymbol(symbol);
            House::deck.push_back(card);
        }
    }
}
Card* House::GetCard() {
    int n = std::rand()%deck.size();
    Card* card = House::deck[n];
    deck.erase(deck.begin()+n);
    return card;
}
std::vector<Card*> House::GetDeck() {
    return House::deck;
}

#endif