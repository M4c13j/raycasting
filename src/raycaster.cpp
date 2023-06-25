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
    float rotSpeed = 2*PI / 75;
    float angle=PI/4 + 0.012412412412412; // angle in radians
    float fov = PI/2;
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
    Color colors[7] = {GREEN,BLUE,YELLOW,RED,PINK,WHITE, WHITE}; // colors for map ( primitive textures )

    Raycaster();
    int atPos( Vector2 where ); // color at position given by vec2
    void setPos( float _x, float _y); // change position to given one
    void movePlayer(int dir); // we move in the direction we face ( angle ), dir is 1 - front, -1 - back
    float rotatePlayer(float deltaAngle); // change a rotation by an amoutn
    void readInput();
    Vector2 castRay( double deltaAngle ); // returns grid cords of hit.
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

Vector2 Raycaster::castRay( double deltaAngle ) {
    const double eps = 1e-20;
    double alpha = deltaAngle + angle;
    if( alpha >= 2*PI ) alpha -= 2*PI;
    if( alpha < 0 ) alpha += 2*PI;

    double deltaRayX = sin(alpha) == 0 ? eps : 1 / sin(alpha);
    double deltaRayY = cos(alpha) == 0 ? eps : 1 / cos(alpha);
    deltaRayX = fabs(deltaRayX);
    deltaRayY = fabs(deltaRayY);

    double distX = 0;
    double distY = 0;

    int axisX = int(pos.x);
    int axisY = int(pos.y);
    int deltaAxisX = cos(alpha) >= 0 ? 1 : -1;
    int deltaAxisY = sin(alpha) >= 0 ? 1 : -1;

    bool last;
    double distToFirstX, distToFirstY;
    distX = deltaAxisY == 1 ? (float)axisY+1-pos.y : pos.y-(float)axisY; distX *= deltaRayX;
    distY = deltaAxisX  == 1 ? (float)axisX+1-pos.x : pos.x-(float)axisX; distY *= deltaRayY;

    while( map[ axisY ][ axisX ] == 0 ) {
        if( distX > distY ) {
            // we try to to collide with Y axis
            distY += deltaRayY;
            axisX += deltaAxisX;
            last = 0;
            std::cout << 1;
//            DrawCircle( 30*axisX, 30*(pos.y+distY*sin(alpha)), 4, YELLOW);
        } else {
            distX += deltaRayX;
            axisY += deltaAxisY;
            last = 1;
            std::cout << 0;
//            DrawCircle( 30*(pos.x+distX*cos(alpha)), 30*axisY, 4, BLUE);
        }
//        DrawRectangle(axisX*30+5, axisY*30+5, 20, 20, PURPLE);
    }

    std::cout << "\n";

    axisX += deltaAxisX < 0 ? -deltaAxisX : 0;
    axisY += deltaAxisY < 0 ? -deltaAxisY : 0;
    Vector2 p;
    if( !last ) {
        p.x = axisX;
        p.y = ((float)axisX-pos.x) * tan(alpha) + pos.y;

    } else {
        p.x = ((float)axisY-pos.y) / ( tan(alpha) == 0 ? eps : tan(alpha) ) + pos.x;
        p.y = axisY;
    }

    return p;
}

void Raycaster::drawMap() {
    int side = 30;
    for(int y=0;y<mapHeight;y++) {
        for(int x=0;x<mapWidth;x++) {
            DrawRectangle( x*side, y*side, side, side, BLACK);
            DrawRectangle( x*side+1, y*side+1, side-2, side-2, colors[map[y][x]]);
        }
    }

    int px = pos.x * side, py = pos.y * side;
    DrawCircle( px, py, 5, WHITE);
    DrawLine( px, py, px+40*cos(angle), py+40*sin(angle), WHITE);
    for(int i=0;i<30;i++) {
        auto rayFromMe = castRay((float)(i)*PI/15);
        DrawLine(px, py, int(rayFromMe.x * side), int(rayFromMe.y * side), PINK);
    }

    DrawText(TextFormat("Position: %04.04f %04.04f", pos.x, pos.y), 720,10,22, WHITE);
    DrawText(TextFormat("Angle: %04.04f ( %04.02f deg )", angle, (360*angle/(2*PI))), 720,30,22, WHITE);
}
#endif //RAYCASTING_RAYCASTER_H