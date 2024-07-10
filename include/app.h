#ifndef APP_H
#define APP_H

#include <iostream>
#include <raylib.h>
#include <utility>
#include <vector>

#define CASTLETON (Color){0, 86, 59, 255} // Castleton green
#define BANGLADESH (Color){0, 106, 78, 255} // Bangladesh green
#define ROSE (Color){178,28,14, 255} // Rose red

const std::pair<int, int> SCREENSIZE = {1080, 720};
const int FPS = 60;

class App {
    public:
        void LoadImages();
        void Init();
        void Run();
        std::vector<Texture2D> textures = {};
        enum gamestate {
            BET,
            START,
            TAKECARDS,
            DEALERCARDS,
            WIN,
            LOSS,
            TIE,
            TOTALLOSS
        };
        enum textures {
            KEYZICON = 53,
            KEYXICON = 54,
            KEYVICON = 56,
            KEYCICON = 57
        };
        int gamestate = 0; // enum gamestate <-
        int ticks = 0;
};

#endif