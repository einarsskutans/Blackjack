#include <iostream>
#include <raylib.h>
#include "app.cpp"

using namespace std;

int main () {
    App* blackjack = new App();
    blackjack->Init();
    blackjack->Run();

    delete blackjack;

    return 0;
}