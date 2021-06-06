#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "../include/raylib.h"
#include "constants.hpp"
#include <math.h>
#include <string>
class Player {
public:
    int fov = 90;        // field of view
    double angle=90;      // angle that player is rotated ( in degrees )
    double deltaAngle=1; // change of angle while rotating
    
    Vector2 position = {12,12}; // vector representing cordinatess
    double step = 0.01f; // position change distance
    
    Vector2 move( float dang ); // move player to 'where'
    void rotate( int dang ); // roate player
    void info();

};

void Player::rotate( int dang ) {
    angle += deltaAngle * dang;
    //if( angle < 0 ) angle += 360;
    //if( angle >= 360 ) angle -= 360;
    
};


Vector2 Player::move( float dang ) {
    Vector2 next;
    
    double theta = (angle + dang) * DEG2RAD;
    next.x = position.x + step * cos(theta);
    next.y = position.y + step * sin(theta);

    position = next;

    return next;
}

void Player::info() {
    DrawText( TextFormat( "Pos: %04.04f /  %04.04f ", position.x , position.y ) , 0 , 0 , 20 , WHITE);
    DrawText( TextFormat( "Angle: %03f", angle ) , 0 , 30 , 20 , WHITE);

} 
#endif