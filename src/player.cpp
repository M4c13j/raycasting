#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "../include/raylib.h"
#include "constants.hpp"

class Player {
public:
    int fov = 90;        // field of view
    float angle=90;      // angle that player is rotated ( in degrees )
    float deltaAngle=1; // change of angle while rotating
    
    Vector2 position = {12,12}; // vector representing cordinatess
    float step; // position change distance
    
    void move( Vector2 where ); // move player to 'where'
    void rotate( int dang ); // roate player
    Vector2 calculateNextPos( float deg ); // return position after move

};

void Player::rotate( int dang ) {
    angle += deltaAngle * dang;
}

void Player::move( Vector2 where ) {
    return;
}

Vector2 Player::calculateNextPos( float deg ) {
    
}


#endif