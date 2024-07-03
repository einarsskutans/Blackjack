#ifndef CARD_H
#define CARD_H

#include "sprite.h"
#include "app.h"
#include <vector>

class Card : public Sprite {
    public:
        Card(std::pair<int, int> ppos, std::pair<int, int> pvel, std::pair<int, int> psize);
        int GetValue();
        void SetValue(int newvalue);
        void Draw(std::vector<Texture2D> textures);
    private:
        int value;
        char* symbol; // Might not be relevant
};

#endif