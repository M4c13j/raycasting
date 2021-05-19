#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "../include/raylib.h"
#include "constants.hpp"

class Player {
private:
    int fov;        // field of view
    int angle;      // angle that player is rotated ( in degrees )
    int deltaAngle; // change of angle while rotating
    
    Vector2 position; // vector representing cordinatess
    float step; // position change distance
    
public:
    
};

#endif