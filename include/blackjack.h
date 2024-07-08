#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>
#include <string>
#include "card.h"

class Player { // Also the dealer
    public:
        Player(std::string pname);

        std::string GetPlayerName();

        bool Hit();
        int GetDeckSum();
        std::vector<Card*> GetDeck();
        void ResetDeck();
        void SetBalance(int newbalance);
        int GetBalance();
        void SetBet(int newbet);
        int GetBet();

        // Graphics
        void DrawCards(std::vector<Texture2D> textures, std::pair<int, int> position, std::pair<int, int> offset);
    private:
        std::vector<Card*> deck;
        std::string name;
        int balance = 200;
        int bet = 0;
};

class House {
    public:
        static void GenerateDeck();
        static Card* GetCard();
        static std::vector<Card*> GetDeck();
    private:
        static std::vector<Card*> deck;
};

#endif