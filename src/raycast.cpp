#ifndef RAYCAST_CPP
#define RAYCAST_CPP

#include "../include/raylib.h"
#include "constants.hpp"
#include "player.cpp"
#include <cmath>

class Raycast 
{
    public:
        float scale;                                                     // scale of the raycasting ( for up/down - scaling )
        int offset;       // shift the position of raycast
        int mapHeight = 24;                                              // delete 24
        int mapWidth = 24;                                               // delete in the future
        int mapa[24][24] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,1,0,1,4,0,3,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,4,3,2,0,4,4,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

        Color colors[6] = {GREEN,BLUE,YELLOW,RED,PINK,WHITE}; // colors for map ( primitive textures )


        Raycast( float scale); // constructor
        void drawSegment( int x, int len , int col ); // draw 1 line on the screen
        void ray( int x , Player &player); // calculate segment
        void draw( Player &player );                                      // draw class that takes a player data
        void resetScreen();                                              // draw a rectngle and clear the screen
        void setMap();

};

Raycast::Raycast( float _scale ) {
    scale = _scale;
}

void Raycast::drawSegment( int x, int len , int col ) {
    DrawRectangle( x , SCREEN_HEIGHT/2 - len/2 , 1, len , colors[col-1] );
}


void Raycast::ray( int X , Player &player ) {
    float x = player.position.x , y = player.position.y;

    double theta = player.angle - player.fov * X / SCREEN_WIDTH;
    double sinus = sin(theta*DEG2RAD) , cosinus = cos(theta*DEG2RAD);

    double deltaX = 1 / sinus , deltaY = 1 / cosinus;
    // double distX = std::abs(1-floor(x)) * deltaX , distY = std::abs(1-floor(y)) * deltaY;

    // int stepX = (sinus>0?1:-1) , stepY = (cosinus>0?1:-1);

    double distX,distY;
    int stepX, stepY;

    if( sinus > 0 ) {
        stepX = 1;
        distX = (1-floor(y)) * deltaY;
    } else {
        stepX = -1;
        distX = floor(y) * deltaY;
    }

    if( cosinus > 0 ) {
        stepY = 1;
        distY = (1-floor(x)) * deltaY;
    } else {
        stepY = -1;
        distY = floor(x) * deltaY;
    }

    while( mapa[(int)x][(int)y] == 0 ) {
        if( distX < distY ) {
            distX += deltaX;
            x += stepX;
        } else {
            distY += deltaY;
            y += stepY;
        }
    }

    double dist = sqrt( pow(player.position.x-x,2) + pow(player.position.y-y,2) );

    drawSegment( X , SCREEN_HEIGHT/(2*dist) , mapa[(int)x][(int)y] );
}


void Raycast::draw( Player &player ) {
    for( int i = 0 ; i < SCREEN_WIDTH ; i++ ) {
        ray( i , player );
    }
}


void Raycast::resetScreen() {
    ClearBackground( BLACK );
    // in the future:
    // 2 rectangles
    // skybox
}


void Raycast::setMap() {
    // download map from file etc.
    return;
}


#endif