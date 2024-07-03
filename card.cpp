#include <raylib.h>
#include "include/card.h"
#include "include/app.h"

Card::Card(std::pair<int, int> ppos, std::pair<int, int> pvel, std::pair<int, int> psize) {
    SetPos(ppos);
    SetVel(pvel);
    SetSize(psize);
}

int Card::GetValue() {
    return value;
}
void Card::SetValue(int newvalue) {
    value = newvalue;
}
void Card::Draw(std::vector<Texture2D> textures) {
    DrawTexture(textures[value-1], GetPos().first - GetSize().first/2, GetPos().second - GetSize().second/2, WHITE);
}
