#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "../include/raylib.h"
#include "constants.hpp"

class Player {
private:
    int fov;        // field of view
    double angle;      // angle that player is rotated ( in degrees )
    double deltaAngle=1; // change of angle while rotating
    
    Vector2 position; // vector representing cordinatess
    float step_sis; // position change distance
    
public:
    void move( Vector2 where ); // move player to 'where'
    Vector2 calculateNextPos(  ); // return position after move
    
};

Vector2 Player::calculateNextPos( ) {
    Vector2 vector_helper;// vector used to scale himself if eg. W and D are pressed
    if(IsKeyDown(KEY_RIGHT)==true && IsKeyDown(KEY_LEFT)==false){ // right rotation by deltaAngle
        angle-=deltaAngle;
    }
    if(IsKeyDown(KEY_RIGHT)==false && IsKeyDown(KEY_LEFT)==true){//left rotation by deltaAngle
        angle+=deltaAngle;
    }

    //*checking all the W,S,A,D states by force... and then calculating next position using "angle" variable.*//

    if(IsKeyDown(KEY_W)==true){

    }

}

void Player::move( Vector2 where ) {
    return;
}


#endif