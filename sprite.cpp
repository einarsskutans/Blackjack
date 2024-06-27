#include "include/sprite.h"

std::pair<int, int> Sprite::GetPos() {
    return position;
};
std::pair<int, int> Sprite::GetVel() {
    return velocity;
};
std::pair<int, int> Sprite::GetSize() {
    return size;
};
void Sprite::SetPos(std::pair<int, int> newpos) {
    position = newpos;
};
void Sprite::SetVel(std::pair<int, int> newvel) {
    velocity = newvel;
};
void Sprite::SetSize(std::pair<int, int> newsize) {
    size = newsize;
};
void Sprite::Move(std::pair<int, int> newpos) {
    position = newpos;
}