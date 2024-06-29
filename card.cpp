#include <raylib.h>
#include "include/card.h"

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
void Card::Draw() {
    DrawRectangle(GetPos().first, GetPos().second, GetSize().first, GetSize().second, WHITE);
}
