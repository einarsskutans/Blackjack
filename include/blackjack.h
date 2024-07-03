#ifndef BLACKJACK_H
#define BLACKJACK_H

/*
    Quick notes - dealer here is at a disatvantage as there is no tie when both players
    take cards of 21 total, the dealer will always lose :(
*/

#include <vector>
#include <string>
#include "card.h"

class Player { // Also the dealer
    public:
        Player(std::string pname);

        std::string GetPlayerName();

        bool Hit();
        bool Stand();
        int GetDeckSum();
        std::vector<Card*> GetDeck();
        void PrintDeck();
        void ResetDeck();

        // Graphics
        void DrawCards(std::vector<Texture2D> textures, std::pair<int, int> position, std::pair<int, int> offset);

    private:
        std::vector<Card*> deck;
        std::string name;
};

class Blackjack {
    public:
        // Core
        void Run();
    private:
        std::vector<Card*> deck;
        bool gamestate = true;
};

#endif