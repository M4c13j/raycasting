#include <raylib.h>

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        const char* text = "OMG! IT WORKS!";

        EndDrawing();
    }


    CloseWindow();
    return 0;
}