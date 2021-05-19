#ifndef RAYCAST_CPP
#define RAYCAST_CPP

#include "raylib.h"
#include "constants.hpp"
#include "player.cpp"
#include <cmath>

class Raycast 
{
    private:
        int screenHight; // height of the screen
        int screenWidth; // width of the screen
        float scale; // scale of the raycasting ( for up/down - scaling )


    public:
        Raycast( Player player , int _screenWidth , int _screenHeight ); //constructor of the class
        void draw( Player player ); // draw class that takes a player data
        void resetScreen(); // draw a rectngle and clear the screen
        float degToRad( int deg ); // deg to rad it is just that

};

Raycast::Raycast( Player player , int _screenWidth , int _screenHeight ) {

}

void Raycast::draw( Player player ) {

}

void Raycast::resetScreen() {

}

float Raycast::degToRad( int deg ) {
    return PI * deg / 360;
}


#endif