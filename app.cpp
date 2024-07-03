#include <raylib.h>
#include "include/card.h"
#include "include/app.h"
#include "include/blackjack.h"

void App::LoadImages() {
    for (int i = 1; i < 55; i++) {
        Image cardImage = LoadImage(TextFormat("assets/card%i.png", i));
        if (i < 53) { // For card assets only
            ImageResizeNN(&cardImage, 128, 128);
        }
        Texture2D cardTexture = LoadTextureFromImage(cardImage);
        UnloadImage(cardImage);
        textures.push_back(cardTexture);
    }
}

void App::Init() {
    InitWindow(SCREENSIZE.first, SCREENSIZE.second, "Blackjack"); 
    LoadImages();
    SetTargetFPS(FPS);
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
        WIN,
        LOSS
    };
    int ticks = 0;

    while (WindowShouldClose() == false){
        ticks++;
        BeginDrawing();

        // Window deco
        ClearBackground(CASTLETON);
        DrawRectangle(0, SCREENSIZE.second/2, SCREENSIZE.first, SCREENSIZE.second/2, {BANGLADESH});
        
        int dealersum = dealer->GetDeckSum();
        if (player->GetDeckSum() > 21) DrawText(TextFormat("%i", player->GetDeckSum()), 0+10, SCREENSIZE.second-40, 30, ROSE);
        else DrawText(TextFormat("%i", player->GetDeckSum()), 0+10, SCREENSIZE.second-40, 30, BLACK);
        if (dealer->GetDeckSum() > 21) DrawText(TextFormat("%i", dealersum), 0+10, SCREENSIZE.second/2-40, 30, ROSE);
        else DrawText(TextFormat("%i", dealersum), 0+10, SCREENSIZE.second/2-40, 30, BLACK);
        DrawTexture(textures[52], SCREENSIZE.first-116, SCREENSIZE.second/2+16, WHITE);
        DrawText("Hit", SCREENSIZE.first-82, SCREENSIZE.second/2+20, 24, WHITE);
        DrawTexture(textures[53], SCREENSIZE.first-116, SCREENSIZE.second/2+64, WHITE);
        DrawText("Stand", SCREENSIZE.first-82, SCREENSIZE.second/2+68, 24, WHITE);

        //DrawText(TextFormat("%i", ticks), 0, 0, 30, RED); // uncomment for ticks debug

        switch (gamestate)
        {
        case START: // Game start; take 2 cards
            House::GenerateDeck();
            dealer->Hit();
            dealer->Hit();
            player->Hit();
            player->Hit();
            gamestate = 1;
            break;
        case TAKECARDS: // Taking cards
            // Conditions
            if (player->GetDeckSum() > 21) {
                ticks = 0;
                gamestate = 4;
                break;
            }
            if (player->GetDeckSum() == 21) {
                ticks = 0;
                gamestate = 3;
                break;
            }
            //


            // Key events
            if (IsKeyDown(KEY_Z) && keyIsUpZ) {
                keyIsUpZ = false;
                player->Hit();
            }            
            if (IsKeyDown(KEY_X) && gamestate == 1 && keyIsUpX) {
                ticks = 0;
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
            if (ticks > FPS * 1) {
                ticks = 0;
                if (dealer->GetDeckSum() > player->GetDeckSum() && dealer->GetDeckSum() < 22) {
                    ticks = 0;
                    gamestate = 4;
                    break;
                }
                if (dealer->GetDeckSum() <= player->GetDeckSum()) {
                    dealer->Hit();
                    break;
                }
                if (dealer->GetDeckSum() > 21) {
                    ticks = 0;
                    gamestate = 3;
                    break;
                }
            }
            break;
        case WIN:
            DrawText("You win", 0+10, SCREENSIZE.second/2 + 40, 30, BLACK);
            if (ticks > FPS * 1.5) {
                ticks = 0;
                gamestate = 0;
                player->ResetDeck();
                dealer->ResetDeck();
                break;
            }
            break;
        case LOSS:
            DrawText("You lose", 0+10, SCREENSIZE.second/2 + 40, 30, BLACK);
            if (ticks > FPS * 1.5) {
                ticks = 0;
                gamestate = 0;
                player->ResetDeck();
                dealer->ResetDeck();
                break;
            }
            break;

        default:
            break;
        }
        if (player->GetDeck().size() > 0) {
            player->DrawCards(textures, {SCREENSIZE.first/2, SCREENSIZE.second*0.64}, {-player->GetDeck()[0]->GetSize().first/4, player->GetDeck()[0]->GetSize().second/6}); // Always keep cards drawn
        }
        if (dealer->GetDeck().size() > 0) {
            dealer->DrawCards(textures, {SCREENSIZE.first/2, SCREENSIZE.second*0.2}, {10, 0});
        }
        EndDrawing();
    }
    player->PrintDeck();
    delete player;
    CloseWindow();
} 