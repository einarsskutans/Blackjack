#ifndef BLACKJACK
#define BLACKJACK

/*
    Quick notes - dealer here is at a disatvantage as there is no tie when both players
    take cards of 21 total, the dealer will always lose :(
*/

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
    //Card* card = new Card({SCREENSIZE.first/2, SCREENSIZE.second/2}, {0, 0}, {64, 128});
    //card->SetValue(std::rand()%12+1);
    Card* card = House::GetCard();
    deck.push_back(card);
    return true;
};
bool Player::Stand() {
    return true;
};
int Player::GetDeckSum() {
    int sum = 0;
    for (Card* card : deck) {
        sum += card->GetValue();
    }
    return sum;
};
std::vector<Card*> Player::GetDeck() {
    return deck;
};
void Player::PrintDeck() {
    std::string mydeck;
    mydeck = "";
    for (Card* card : deck) {
        switch (card->GetValue())
            {
            case 1:
                mydeck += "ace\n";
                break;
            case 11:
                mydeck += "valet\n";
                break;
            case 12:
                mydeck += "queen\n";
                break;
            case 13:
                mydeck += "king\n";
                break;
            
            default:
                mydeck += std::to_string(card->GetValue()) + "\n";
            }
    }
    std::cout << mydeck;
}
void Player::ResetDeck() {
    deck = {};
};

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
    for (int value = 1; value < 14; value++) {
        for (int row = 0; row < 4; row++) {
            Card* card = new Card({SCREENSIZE.first/2, SCREENSIZE.second/2}, {0, 0}, {64, 128});
            card->SetValue(value);
            House::deck.push_back(card);
        }
    }
}
Card* House::GetCard() {
    return House::deck[std::rand()%deck.size()];
}
std::vector<Card*> House::GetDeck() {
    return House::deck;
}

#endif