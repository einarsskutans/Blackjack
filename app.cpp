#include <iostream>
#include <utility>
#include <raylib.h>
#include "blackjack.cpp"

class App {
    public:
        // Raylib
        void Init() {
            Blackjack* blackjack = new Blackjack();
            blackjack->Run();

            InitWindow(screensize.first, screensize.second, "Test");
            SetTargetFPS(60);
        }
        void Run() {
            while (WindowShouldClose() == false){
                BeginDrawing();
                ClearBackground(BLACK);

                DrawCircle(200,200,50, WHITE);

                EndDrawing();
            }
            CloseWindow();
        }

    private:
        std::pair<int, int> screensize{450, 450};
};