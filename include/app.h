#ifndef APP_H
#define APP_H

#include <iostream>
#include <raylib.h>
#include <utility>

const std::pair<int, int> SCREENSIZE = {450, 450};

class App {
    public:
        void Init();
        void Run();
};

#endif