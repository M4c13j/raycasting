#ifndef RAYCASTER_CPP
#define RAYCASTER_CPP

#include "raylib.h"
#include <cmath>
#include <string>
#include <iostream>

class Raycaster {
public:
    Vector2 speed = {0.065f, 0.065f};
    Vector2 pos = {7,11};
    float rotSpeed = 2*PI / 120;
    float angle=PI/4; // angle in radians
    int mapWidth = 24;
    int mapHeight = 24;
    int map[24][24] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
            {1,0,0,0,0,6,0,0,0,0,2,0,0,0,0,4,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,6,0,0,0,0,3,0,2,4,0,3,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,6,6,0,0,0,4,3,2,3,4,3,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    Color colors[6] = {GREEN,BLUE,YELLOW,RED,PINK,WHITE}; // colors for map ( primitive textures )

    Raycaster();
    int atPos( Vector2 where ); // color at position given by vec2
    void setPos( float _x, float _y); // change position to given one
    void movePlayer(int dir); // we move in the direction we face ( angle ), dir is 1 - front, -1 - back
    float rotatePlayer(float deltaAngle); // change a rotation by an amoutn
    void readInput();
    Vector2 castRay();
    void drawMap();
};

Raycaster::Raycaster() {
    return;
}

int Raycaster::atPos(Vector2 where) {
    return map[ int(where.y) ][ int(where.x) ];
}

void Raycaster::setPos(float _x, float _y) {
    pos = {_x, _y};
}

void Raycaster::movePlayer(int dir) {
    Vector2 newPos = pos;
    newPos.x += speed.x * cos(angle) * dir;
    newPos.y += speed.y * sin(angle) * dir;
//    std::cout << "Attempt to move to " << newPos.x << " " << newPos.y << "   " << atPos(newPos) << std::endl;
    if( atPos( newPos ) != 0 ) return; // no moving today
    pos = newPos;
//    std::cout << "Moved to " << pos.x << " " << pos.y << std::endl;
}

float Raycaster::rotatePlayer(float deltaAngle) {
    angle += deltaAngle;
    if( angle >= 2*PI ) angle -= 2*PI;
    if( angle < 0 ) angle += 2*PI;
//    std::cout << "Rotated. Angle: " << angle << "\n";
    return angle;
}

void Raycaster::readInput() {
    if( IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) ) rotatePlayer( (-1)*rotSpeed );
    if( IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) ) rotatePlayer( rotSpeed );
    if( IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) ) movePlayer(1);
    if( IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) ) movePlayer(-1);
}

Vector2 Raycaster::castRay() {

}

void Raycaster::drawMap() {
    int side = 30;
    for(int y=0;y<mapHeight;y++) {
        for(int x=0;x<mapWidth;x++) {
            DrawRectangle( x*side, y*side, side, side, BLACK);
            DrawRectangle( x*side+1, y*side+1, side-2, side-2, colors[map[y][x]]);
        }
    }

    int px = pos.x*side, py = pos.y*side;
    DrawCircle( px, py, 5, WHITE);
    DrawLine( px, py, px+40*cos(angle), py+40*sin(angle), PINK);

    DrawText(TextFormat("Position: %04.04f %04.04f", pos.x, pos.y), 650,10,22, WHITE);
    DrawText(TextFormat("Angle: %04.04f", angle), 650,30,22, WHITE);
    Rectangle()
}
#endif //RAYCASTING_RAYCASTER_H