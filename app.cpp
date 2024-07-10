#include <raylib.h>
#include "include/card.h"
#include "include/app.h"
#include "include/blackjack.h"

void App::LoadImages() {
    for (int i = 1; i < 59; i++) {
        Image cardImage = LoadImage(TextFormat("assets/card%i.png", i));
        if (i < 54) { // For card assets only
            ImageResizeNN(&cardImage, 128, 128);
        }
        if (i == 56) {
            SetWindowIcon(cardImage);
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
    int playersum;
    int dealersum;
    
    Card* housecard = new Card({100, 100}, {0, 0}, {128, 128});
    housecard->SetValue(14); // Backside card value

    while (WindowShouldClose() == false){
        ticks++;
        BeginDrawing();
        playersum = player->GetDeckSum();
        dealersum = dealer->GetDeckSum();

        // Window deco
        ClearBackground(CASTLETON);
        DrawRectangle(0, SCREENSIZE.second/2, SCREENSIZE.first, SCREENSIZE.second/2, {BANGLADESH});

        if (playersum > 21) DrawText(TextFormat("%i", playersum), 0+10, SCREENSIZE.second-40, 30, ROSE);
        else DrawText(TextFormat("%i", playersum), SCREENSIZE.first/108, SCREENSIZE.second-40, 30, BLACK);
        if (dealersum > 21) DrawText(TextFormat("%i", dealersum), 0+10, SCREENSIZE.second/2-40, 30, ROSE);
        else DrawText(TextFormat("%i", dealersum), SCREENSIZE.first/108, SCREENSIZE.second/2-40, 30, BLACK);

        DrawTexture(textures[KEYZICON], SCREENSIZE.first/1.2, SCREENSIZE.second/1.9, WHITE);
        DrawText("Hit", SCREENSIZE.first/1.14, SCREENSIZE.second/1.9+6, 20, WHITE);
        DrawTexture(textures[KEYXICON], SCREENSIZE.first/1.2, SCREENSIZE.second/1.9+40, WHITE);
        DrawText("Stand", SCREENSIZE.first/1.14, SCREENSIZE.second/1.9+46, 20, WHITE);
        DrawTexture(textures[KEYCICON], SCREENSIZE.first/1.2, SCREENSIZE.second/1.9+240, WHITE);
        DrawText("Bet incr.", SCREENSIZE.first/1.14, SCREENSIZE.second/1.9+246, 20, WHITE);
        DrawTexture(textures[KEYVICON], SCREENSIZE.first/1.2, SCREENSIZE.second/1.9+280, WHITE);
        DrawText("Bet decr.", SCREENSIZE.first/1.14, SCREENSIZE.second/1.9+286, 20, WHITE);

        DrawText(TextFormat("Balance: $%i", player->GetBalance()), SCREENSIZE.first/108, SCREENSIZE.second/1.9, 20, WHITE);
        if (player->GetBalance()>-1000)
        DrawText(TextFormat("Bet: $%i", player->GetBet()), SCREENSIZE.first/108, SCREENSIZE.second/1.9+36, 20, WHITE);
        else if (player->GetBalance()<-999)
        DrawText(TextFormat("Bet: LIFE SAVINGS", player->GetBet()), SCREENSIZE.first/108, SCREENSIZE.second/1.9+36, 20, WHITE);

        //DrawText(TextFormat("%i", ticks), 0, 0, 30, RED); // uncomment for ticks debug

        switch (gamestate)
        {
        case BET:
            if (IsKeyDown(KEY_Z) && keyIsUpZ) {
                keyIsUpZ = false;
                gamestate = START;
                break;
            }
            if (IsKeyUp(KEY_Z)) {
                keyIsUpZ = true;
            }
            if (IsKeyPressed(KEY_C)) {
                player->SetBet(player->GetBet()+50);
                dealer->SetBet(dealer->GetBet()+50);
            }
            if (IsKeyPressed(KEY_V) && player->GetBet() > 50) {
                player->SetBet(player->GetBet()-50);
                dealer->SetBet(dealer->GetBet()-50);
            }
            break;
        case START: // Game start; take 2 cards
            House::GenerateDeck();
            dealer->Hit();
            dealer->Hit();
            player->Hit();
            player->Hit();
            player->AddBalance(-player->GetBet());
            dealer->AddBalance(-dealer->GetBet());
            playersum = player->GetDeckSum();
            dealersum = dealer->GetDeckSum();

            // Conditionals for a Blackjack -> starting cards = 21
            if (dealersum == 21 && playersum == 21) {
                ticks = 0;
                gamestate = TIE;
                break;
            }
            if (dealersum == 21) {
                ticks = 0;
                gamestate = LOSS;
                break;
            }
            if (playersum == 21) {
                ticks = 0;
                gamestate = WIN;
                break;
            }
            gamestate = TAKECARDS;
            break;
        case TAKECARDS: // Taking cards
            // Conditionals
            if (playersum > 21) {
                ticks = 0;
                gamestate = LOSS;
                break;
            }
            if (dealersum > 21) {
                ticks = 0;
                gamestate = WIN;
                break;
            }

            // Key events
            if (IsKeyDown(KEY_Z) && keyIsUpZ) {
                keyIsUpZ = false;
                player->Hit();
            }            
            if (IsKeyDown(KEY_X) && gamestate == TAKECARDS && keyIsUpX) {
                ticks = 0;
                keyIsUpX = false;
                gamestate = DEALERCARDS;
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
                if (dealersum > 21) {
                    ticks = 0;
                    gamestate = WIN;
                    break;
                }
                if (dealersum == 21 && playersum == 21) {
                    gamestate = TIE;
                }
                if (dealersum > playersum && dealersum < 22) {
                    ticks = 0;
                    gamestate = LOSS;
                    break;
                }
                if (dealersum <= playersum && dealersum != 21) {
                    dealer->Hit();
                    break;
                }
            }
            break;
        case WIN:
            DrawText("You win", SCREENSIZE.first/108, SCREENSIZE.second/1.9 + 66, 30, BLACK);
            if (ticks > FPS * 1.5) {
                ticks = 0;
                if (player->GetBalance()>-1000) {
                    gamestate = BET;
                    player->AddBalance(player->GetBet()+dealer->GetBet());
                }
                if (player->GetBalance()<-999) {
                    gamestate = BET;
                    player->SetBalance(50);
                }
                player->ResetDeck();
                dealer->ResetDeck();
                break;
            }
            break;
        case LOSS:
            DrawText("You lose", SCREENSIZE.first/108, SCREENSIZE.second/1.9 + 66, 30, BLACK);
            if (ticks > FPS * 1.5) {
                ticks = 0;
                if (player->GetBalance()>-1000) gamestate = BET;
                if (player->GetBalance()<-999) gamestate = TOTALLOSS;
                dealer->AddBalance(player->GetBet()+dealer->GetBet());
                player->ResetDeck();
                dealer->ResetDeck();
                break;
            }
            break;
        case TIE:
            DrawText("Tie", SCREENSIZE.first/108, SCREENSIZE.second/1.9 + 66, 30, BLACK);
            if (ticks > FPS * 1.5) {
                ticks = 0;
                gamestate = BET;
                player->AddBalance(player->GetBet());
                dealer->AddBalance(dealer->GetBet());
                player->ResetDeck();
                dealer->ResetDeck();
                break;
            }
        case TOTALLOSS:
            DrawText("You lost all of your money, whoops?\n\n\nWell you can't continue, quit now.", SCREENSIZE.first/108, SCREENSIZE.second/1.9 + 66, 30, BLACK);
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
    for (Card* card : player->GetDeck()) {
        delete card;
    }
    for (Card* card : dealer->GetDeck()) {
        delete card;
    }
    for (Card* card : House::GetDeck()) {
        delete card;
    }
    delete player;
    delete dealer;
    CloseWindow();
} 