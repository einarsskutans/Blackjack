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
    /*
    int offset = GetSize().first * 0.08;
    int textsize = GetSize().first * 0.4;
    if (value != 1) {
        DrawRectangle(GetPos().first - GetSize().first/2, GetPos().second - GetSize().second/2, GetSize().first, GetSize().second, BLACK); // BLACK background -> outline
        DrawRectangle(
            (GetPos().first - GetSize().first/2) + offset,
            (GetPos().second - GetSize().second/2) + offset,
            GetSize().first - offset*2,
            GetSize().second - offset*2,
            WHITE
        ); // WHITE foreground -> card
        DrawText(TextFormat("%i", GetValue()), GetPos().first - textsize/4, GetPos().second - textsize/2, textsize, BLACK); // BLACK Card value
    }*/
    DrawTexture(textures[value-1], GetPos().first - GetSize().first/2, GetPos().second - GetSize().second/2, WHITE);
}
