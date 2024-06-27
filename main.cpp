#include "include/app.h"

int main () {
    App* app = new App();
    app->Init();
    app->Run();

    std::cout << "hello";

    delete app;

    return 0;
}