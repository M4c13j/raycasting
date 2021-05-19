#include "raylib.h"
#include "constants.hpp"

class Player {
    int fov;        // field of view
    int angle;      // angle that player is rotated ( in degrees )
    int deltaAngle; // change of angle while rotating
    
    Vector2 position; // vector representing cordinatess
    float step; // position change distance
    
public:
    
};