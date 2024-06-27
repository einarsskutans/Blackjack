#include <raylib.h>
#include "include/card.h"
#include "include/app.h"

void App::Init() {
    InitWindow(screensize.first, screensize.second, "Test");
    SetTargetFPS(60);

    // test
    
}
void App::Run() {
    Card* card = new Card({20, 20}, {20, 20}, {20, 20});
    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(GRAY);

        card->Draw();

        EndDrawing();
    }
    CloseWindow();
}