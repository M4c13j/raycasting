#ifndef INPUT_CPP
#define INPUT_CPP

#include "../include/raylib.h"
#include "constants.hpp"
#include "player.cpp"

bool readInput( Player &player) {
    if( IsKeyDown(KEY_A) ) player.rotate(1);
    if( IsKeyDown(KEY_D) ) player.rotate(-1);
    
}

#endif