#include <raylib.h>
#include "player.cpp"
#include "raycaster.cpp"

constexpr auto SCREEN_WIDTH  = 1200;
constexpr auto SCREEN_HEIGHT = 800;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster demo");
    SetTargetFPS(60);

    Raycaster raycaster = Raycaster();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        raycaster.readInput();
        raycaster.drawMap();

        EndDrawing();
    }


    CloseWindow();
    return 0;
}