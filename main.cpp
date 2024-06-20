#include <iostream>
#include <raylib.h>
#include "app.cpp"
#include "blackjack.cpp"

using namespace std;

int main () {
    
    /*
    App* blackjack = new App();
    blackjack->Init();
    blackjack->Run();

    delete blackjack;
    */

    Blackjack* blackjack = new Blackjack();
    blackjack->Run();
    delete blackjack;

    return 0;
}