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
    Player* dealer = new Player("Jack");

    bool keyIsUpZ;
    bool keyIsUpX;
    int gamestate = 0; // (0) - take 2 cards; (1) - keep taking cards; (2) - compare cards with dealer; (3) - game ends
    enum gamestate {
        START,
        TAKECARDS,
        DEALERCARDS,
        END
    };

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText(TextFormat("%i", player->GetDeckSum()), SCREENSIZE.first/4, SCREENSIZE.second/4, 30, BLACK);

        switch (gamestate)
        {
        case START: // Game start; take 2 cards
            player->Hit();
            player->Hit();
            gamestate = 1;
            break;
        case TAKECARDS: // Taking cards
            // Conditions
            if (player->GetDeckSum() > 21) {
                gamestate = 3;
                DrawText("You lose", SCREENSIZE.first/2, SCREENSIZE.second/4, 30, BLACK);
                break;
            }
            if (player->GetDeckSum() == 21) {
                gamestate = 3;
                DrawText("You win", SCREENSIZE.first/2, SCREENSIZE.second/4, 30, BLACK);
                break;
            }
            //


            // Key events
            if (IsKeyDown(KEY_Z) && keyIsUpZ) {
                keyIsUpZ = false;
                player->Hit();
            }            
            if (IsKeyDown(KEY_X) && gamestate == 1 && keyIsUpX) {
                keyIsUpX = false;
                gamestate = 2;
                break;
            }
            if (IsKeyUp(KEY_Z)) {
                keyIsUpZ = true;
            }
            if (IsKeyUp(KEY_X)) {
                keyIsUpX = true;
            }
        
            break;
        case DEALERCARDS:
            dealer->Hit();
            if (dealer->GetDeckSum() > 21) {
                gamestate = 3;
                DrawText("You win", SCREENSIZE.first/2, SCREENSIZE.second/4, 30, BLACK);
                break;
            }
            if (dealer->GetDeckSum() > player->GetDeckSum()) {
                gamestate = 3;
                DrawText("You lose", SCREENSIZE.first/2, SCREENSIZE.second/4, 30, BLACK);
                break;
            }
        case END:
            gamestate = 0;
            player->ResetDeck();
            break;

        default:
            break;
        }
        player->DrawCards(); // Always keep cards drawn

        EndDrawing();
    }
    player->PrintDeck();
    delete player;
    CloseWindow();
} 