#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "../include/raylib.h"
#include "constants.hpp"

class Player {
private:
    int fov;        // field of view
    float angle;      // angle that player is rotated ( in degrees )
    float deltaAngle; // change of angle while rotating
    
    Vector2 position; // vector representing cordinatess
    float step; // position change distance
    
public:
    void move( Vector2 where ); // move player to 'where'
    Vector2 calculateNextPos( float deg ); // return position after move
    
};

void Player::move( Vector2 where ) {
    return;
}

Vector2 Player::calculateNextPos( float deg ) {
    
}

#endif