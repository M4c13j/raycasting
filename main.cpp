#include "include/raylib.h"

int main(int argc, char* argv[])
{
    int screenWidth = 900;
    int screenHeight = 500;

    // class inits
    
    // raylib stuff
    InitWindow(screenWidth, screenHeight, "Raycasting engine -- Raye");
    SetTargetFPS(60);



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // variables etc.


        // Drawing part
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Sneeeeeeed", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        // End drawing
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

// gcc main.c -o game.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm