#include "include/raylib.h"
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

    raycast.graphics.LoadTextures();
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {


        BeginDrawing();

            readInput( player );
            raycast.resetScreen();
            //raycast.drawMap( player );
            raycast.draw( player );
            
            player.info();

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

// gcc main.c -o game.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
// clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -std=c++17 lib/libraylib.a main.cpp -o main