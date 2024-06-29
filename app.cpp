#include <raylib.h>
#include "include/card.h"
#include "include/app.h"
#include "include/blackjack.h"

void App::Init() {
    InitWindow(SCREENSIZE.first, SCREENSIZE.second, "Test");
    SetTargetFPS(60);

    // test
    
}
void App::Run() {
    Player* player = new Player("Tom");
    player->Hit();
    player->Hit();
    player->Hit();
    player->Hit();
    player->Hit();
    player->Hit();
    player->Hit();
    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(GRAY);

        player->DrawCards();


        EndDrawing();
    }
    player->PrintDeck();
    delete player;
    CloseWindow();
}