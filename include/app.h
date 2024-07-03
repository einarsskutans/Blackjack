#ifndef APP_H
#define APP_H

#include <iostream>
#include <raylib.h>
#include <utility>
#include <vector>

const std::pair<int, int> SCREENSIZE = {720, 540};
const int FPS = 60;

class App {
    public:
        void LoadImages();
        void Init();
        void Run();
        std::vector<Texture2D> textures = {};
};

#endif