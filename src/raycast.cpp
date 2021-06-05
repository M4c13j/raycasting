#ifndef RAYCAST_CPP
#define RAYCAST_CPP

#include "../include/raylib.h"
#include "constants.hpp"
#include "player.cpp"
#include <cmath>
#include <stdio.h>
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
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,4,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,3,0,2,4,0,3,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,4,3,2,3,4,3,0,0,0,0,0,0,0,1},
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
        void drawSegment( int x, int len , Color color ); // draw 1 line on the screen
        void ray( int x , Player &player); // calculate segment
        void draw( Player &player );                                      // draw class that takes a player data
        void resetScreen();                                              // draw a rectngle and clear the screen
        void drawMap( Player &player);
        void setMap();

};

double r2d( double x , int i ) {
    return roundf(x*pow(10,i))/pow(10,i);
}

Raycast::Raycast( float _scale ) {
    scale = _scale;
}

void Raycast::drawSegment( int x, int len , Color color ) {
    DrawRectangle( x , SCREEN_HEIGHT/2 - len/2 , 1, len , color );
}


void Raycast::ray( int i , Player &player ) {
    double x = player.position.x , y = player.position.y;
    int mapX = int(x) , mapY = int(y);
    double theta = ( (double)player.angle + player.fov / 2 - player.fov * (double)(i) / (double)(SCREEN_WIDTH) ) * DEG2RAD;
    double sinus = sin(theta) , cosinus = cos(theta);

    double deltaX = abs( 1 / cosinus ) , deltaY = abs(1 / sinus);
    //if( sinus == 0 ) deltaX = 0; if( cosinus == 0 ) deltaY = 0;

    double distX,distY;
    float stepX, stepY;

    if( cosinus >= 0 ) {
        stepX = 1;
        distX = ( mapX - x  + 1 ) * deltaX; // od  drugiej strony łapiemy
    } else {
        stepX = -1;
        distX = ( x - mapX ) * deltaX;
    }

    if( sinus >= 0 ) {
        stepY = 1;
        distY = ( (mapY - y) + 1  ) * deltaY;
    } else {
        stepY = -1;
        distY = ( y - mapY ) * deltaY;
    }

    bool hit = true , side = 0;
    double dist;
    while( mapa[mapY][mapX] == 0 ) {
        // line in while causes raycasting to go black if rays are casted in a tile 
        if( distX < distY ) {
            distX += deltaX;
            mapX += stepX;

            side = 0;
        } else {
            distY += deltaY;
            mapY += stepY;

            side = 1;
        }
    }

    double perpWallDist;
    if (side == 0) perpWallDist = (mapX - x + (1 - stepX) / 2) / cosinus;
      else           perpWallDist = (mapY - y + (1 - stepY) / 2) / sinus;
    double len = SCREEN_HEIGHT/ ( perpWallDist ) ;

    //DrawLine( player.position.x*20 , player.position.y*20 , mapX*20 , mapY*20 , RED );
    
    Color color = colors[mapa[mapY][mapX]-1];
    if( side ) color.a/=2;
    drawSegment( i , len , color );
}


void Raycast::draw( Player &player ) {
    for( int i = 0 ; i < SCREEN_WIDTH ; i++ ) {
        //printf("%f \n", (float)player.angle - 100 * (float)i / (float)SCREEN_WIDTH );
        ray( i , player );
    }
    
}

void Raycast::drawMap( Player &player ) {
    for(int i=0;i<mapHeight;i++) {
        for(int j=0;j<mapWidth;j++) {
            Color col = (mapa[i][j]==0?BLACK:colors[mapa[i][j]-1] );
            DrawRectangle(20*j,20*i,20,20,col);
        }
    }
    DrawCircle(player.position.x*20,player.position.y*20,5,RED);
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