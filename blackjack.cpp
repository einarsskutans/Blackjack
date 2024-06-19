#include <iostream>
#include <vector>
#include <utility>
#include <string>

class Player { // Also the dealer
    public:
        Player(std::string pname) {
            name = pname;
        };

        bool Hit() {
            deck.push_back(2);
            return true;
        };
        bool Stand() {
            return true;
        };
        std::vector<int> GetDeck() {
            return deck;
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
            while (gamestate) { // Main blackjack loop
                player->Hit();
                player->Hit();
                
                for (int i : player->GetDeck()) {
                    std::cout << "\n" << i;
                }

                for (int i = 1; ;) {
                    for (int i : player->GetDeck()) {
                        std::cout << "\n" << i << ", type 0 to fold";
                    }
                    std::cin >> i;
                    if (i == 0) {
                        break;
                    }
                    else {
                        player->Hit();
                    }
                    
                }
            }
        };
    private:
        std::vector<int> deck;
        bool gamestate = false;
};