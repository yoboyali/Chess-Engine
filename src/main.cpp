#include "Includes.h"
#include "renderer.h"


int main()
{
    InitWindow(WindowWidth , WindowHeight , "Chess");
    renderer Game;
    while (!WindowShouldClose()) {
        BeginDrawing();
        HideCursor();
        ClearBackground(WHITE);
        Game.render();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}