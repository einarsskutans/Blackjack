#ifndef CARD_H
#define CARD_H

#include "sprite.h"

class Card : public Sprite {
    public:
        Card(std::pair<int, int> ppos, std::pair<int, int> pvel, std::pair<int, int> psize);
        int GetValue();
        void Draw();
    private:
        int value;
        char* symbol; // Might not be relevant
};

#endif