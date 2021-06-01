#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "../include/raylib.h"
#include "constants.hpp"

class Player {
<<<<<<< HEAD
public:
    int fov = 90;        // field of view
    float angle=90;      // angle that player is rotated ( in degrees )
    float deltaAngle=1; // change of angle while rotating
    
    Vector2 position = {12,12}; // vector representing cordinatess
    float step; // position change distance
=======
private:
    int fov;        // field of view
    double angle;      // angle that player is rotated ( in degrees )
    double deltaAngle=1; // change of angle while rotating
    
    Vector2 position; // vector representing cordinatess
    float step_sis; // position change distance
>>>>>>> e0dc471c851a5318144607a4015abc0343c79c61
    
    void move( Vector2 where ); // move player to 'where'
<<<<<<< HEAD
    void rotate( int dang ); // roate player
    Vector2 calculateNextPos( float deg ); // return position after move

};

void Player::rotate( int dang ) {
    angle += deltaAngle * dang;
=======
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

>>>>>>> e0dc471c851a5318144607a4015abc0343c79c61
}

void Player::move( Vector2 where ) {
    return;
}



#endif