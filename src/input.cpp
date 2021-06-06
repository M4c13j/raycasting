#ifndef INPUT_CPP
#define INPUT_CPP

#include "../include/raylib.h"
#include "constants.hpp"
#include "player.cpp"

bool readInput( Player &player) {
    if( IsKeyDown(KEY_LEFT) ) player.rotate(1);
    if( IsKeyDown(KEY_RIGHT) ) player.rotate(-1);

    if( IsKeyDown(KEY_W) ) player.move( 0 );
    if( IsKeyDown(KEY_S) ) player.move ( 180 );
}

#endif