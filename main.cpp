#include "include/raylib.h"
#include "./src/constants.hpp"
#include "./src/raycast.cpp"
#include "./src/player.cpp"
#include "./src/input.cpp"

int main(int argc, char* argv[])
{

    // class inits

    // raylib stuff
    InitWindow( SCREEN_WIDTH , SCREEN_HEIGHT , "Raycasting engine -- Raye");
    SetTargetFPS( FRAME_LIMIT );

    Player player = Player();
    Raycast raycast = Raycast( 1 );

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {


        BeginDrawing();

        readInput( player );
        raycast.resetScreen();
        raycast.draw( player );

        //DrawText("Sneeeeeeed", 400, 0, 40, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

// gcc main.c -o game.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm