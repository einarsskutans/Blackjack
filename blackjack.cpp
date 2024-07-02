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
    Card* card = new Card({SCREENSIZE.first/2, SCREENSIZE.second/2}, {0, 0}, {60, 120});
    card->SetValue(std::rand()%12+1);
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

void Player::DrawCards() {
    int cardGapX = -deck[0]->GetSize().first/4;
    int cardWidth = deck[0]->GetSize().first;
    int tableWidth = cardWidth * deck.size() + cardGapX * (deck.size() - 1);
    int xpos = (SCREENSIZE.first/2 - tableWidth/2) + cardWidth / 2;
    int ypos = deck[0]->GetPos().second;
    for (Card* card : deck) {
        card->SetPos({xpos, ypos});
        card->Draw();
        xpos += cardGapX + deck[0]->GetSize().first;
        ypos += deck[0]->GetSize().first/4;
    }
};

// Core
void Blackjack::Run() {
    Player* player = new Player("Cena");

    while (gamestate) { // Main blackjack loop
        std::string input = "1";
        player->ResetDeck();
        player->Hit(); // Take 2 cards
        player->Hit();

        player->PrintDeck();
        std::cout << "Total sum: " << player->GetDeckSum() << "\n";

        for (; player->GetDeckSum() < 21; ) { // Taking cards 1/3
            player->PrintDeck();
            std::cout << "Total sum: " << player->GetDeckSum() << " - type 0 to pass.\n";
            std::cin >> input;
            if (input == "0") {
                break;
            }
            else {
                player->Hit();
            }
        }

        if (player->GetDeckSum() == 21) {
            std::cout << player->GetPlayerName() << " wins\n";
        }
        if (player->GetDeckSum() > 21) {
            std::cout << player->GetPlayerName() << " loses\n";
        }

    }
}

#endif