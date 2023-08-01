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

        if(IsKeyDown(KEY_M)) raycaster.drawMap();
        else raycaster.draw();
        DrawText(TextFormat("FPS: %i", GetFPS()), 0,10,22, WHITE);


        EndDrawing();
    }


    CloseWindow();
    return 0;
}

/*
 * Huge thanks to:
 * https://lodev.org/cgtutor/raycasting.html
 */