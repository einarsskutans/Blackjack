#ifndef APP_H
#define APP_H

#include <iostream>
#include <raylib.h>
#include <utility>

class App {
    public:
        void Init();
        void Run();

    private:
        std::pair<int, int> screensize{450, 450};
};

#endif