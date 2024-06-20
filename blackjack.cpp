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

class Player { // Also the dealer
    public:
        Player(std::string pname) {
            name = pname;
        };

        std::string GetPlayerName() {
            return name;
        };

        bool Hit() {
            deck.push_back(std::rand()%13);
            return true;
        };
        bool Stand() {
            return true;
        };
        int GetDeckSum() {
            return std::accumulate(deck.begin(), deck.end(), 0);
        };
        std::vector<int> GetDeck() {
            return deck;
        };
        void PrintDeck() {
            std::string mydeck;
            mydeck = "";
            for (int card : deck) {
                switch (card)
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
                        mydeck += std::to_string(card) + "\n";
                    }
            }
            std::cout << mydeck;
        }
        void ResetDeck() {
            deck = {};
        };

    private:
        std::vector<int> deck;
        std::string name;
};

class Blackjack {
    public:
        // Core
        void Run() {
            Player* player = new Player("Cena");
            Player* dealer = new Player("Weewee");
            while (gamestate) { // Main blackjack loop
                player->ResetDeck();
                std::string input = "1";
                for (; player->GetDeckSum() < 22; ) { // Taking cards 1/3
                    player->Hit(); // Take 2 cards
                    player->Hit();

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

                if (player->GetDeckSum() > 21) { // Card checking 2/3
                    std::cout << player->GetPlayerName() << " lost\n";
                }
                if (player->GetDeckSum() == 21) {
                    std::cout << player->GetPlayerName() << " won\n";
                }

            }
        };
    private:
        std::vector<int> deck;
        bool gamestate = true;
};

#endif