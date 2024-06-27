#ifndef SPRITE_H
#define SPRITE_H

#include <utility>

class Sprite {
    public:
        std::pair<int, int> GetPos();
        std::pair<int, int> GetVel();
        std::pair<int, int> GetSize();
        void SetPos(std::pair<int, int> newpos);
        void SetVel(std::pair<int, int> newvel);
        void SetSize(std::pair<int, int> newsize);
        void Move(std::pair<int, int> newpos);
    private:
        std::pair<int, int> position, velocity, size;
        bool movable, drawable;
};

#endif