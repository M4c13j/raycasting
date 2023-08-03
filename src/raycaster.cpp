#ifndef RAYCASTER_CPP
#define RAYCASTER_CPP

#include "raylib.h"
#include "btextures.cpp"
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

struct Hit{
    float x,y; // hit position ( exact )
    float part;
    int   mapX, mapY; // map cooridnates of hit;
    bool  side;
};

class Raycaster {
public:
    Vector2 pos = {7, 11};
    float   angle = PI / 4 + 0.012412412412412; // angle in radians
    const float fov = PI / 2;
    const int mapWidth = 24;
    const int mapHeight = 24;
    int map[24][24];
    int floor[24][24];
    int ceiling[24][24];
    std::vector<Color> colors;  // colors for map ( primitive textures )
    std::vector<BTexture> textures; // Textures stored in vram
    Texture skyBox;

    Raycaster();

    void loadTextures(); // loading textures from files
    int atPos(Vector2 where); // color at position given by vec2
    void setPos(float _x, float _y); // change position to given one
    void movePlayer(int dir); // we move in the direction we face ( angle ), dir is 1 - front, -1 - back
    float rotatePlayer(float deltaAngle); // change a rotation by an amount
    void readInput(); // handle keyboard, mouse input
    Hit castRay(double deltaAngle); // returns grid cords of collision
    void wallCasting(); // drawing walls
    void floceilCasting(); // cast floor and even ceiling
    void draw(); // draws a 2.5d raycasting
    void drawMap(); // draws a map ( 2d projection )
    void showDebug(); // show debug info on screen
};

Raycaster::Raycaster() {
    int _map[24][24] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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

    for( int i=0;i<mapHeight;i++) {
        for(int j=0;j<mapWidth;j++) {
            map[i][j] = _map[i][j];
            floor[i][j] = (i*mapWidth+j)%2;
            ceiling[i][j] = (i*mapWidth+j)%2;
        }
    }

    colors = std::vector<Color>{GREEN, BLUE, YELLOW, RED, PINK, WHITE, WHITE};

    loadTextures();


}

void Raycaster::loadTextures() {
    Image texMap = LoadImage("../assets/minecraft_old.png");
    Image _skyBox = LoadImage("../assets/sky.png");
    ImageResize( &_skyBox, GetScreenWidth(), GetScreenHeight());
    skyBox = LoadTextureFromImage(_skyBox);

    std::vector<int> ids = {1,2,4,6,7,16*1+9,16*1+0}; // ids to load, numbered from 0 to 256!
    for( int &i : ids ) {
        Image texturePart = ImageFromImage(texMap, {(float)16*(i%16),(float)16*(i/16),16,16});
        BTexture temp;
        temp.loadFromImage( texturePart );
        textures.push_back( temp );
    }

    UnloadImage(_skyBox);
    UnloadImage(texMap);
}

int Raycaster::atPos(Vector2 where) {
    return map[ int(where.y) ][ int(where.x) ];
}

void Raycaster::setPos(float _x, float _y) {
    pos = {_x, _y};
}

void Raycaster::movePlayer(int dir) {
    Vector2 speed = {0.065f, 0.065f};
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
    float rotSpeed = GetFrameTime() * (PI/50) * 60; // deltaTime * UniversalRotationConstant / fpsPerfectForThatConstant ( fr bro )
    if( IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) ) rotatePlayer( rotSpeed );
    if( IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) ) rotatePlayer( -rotSpeed );
    if( IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) ) movePlayer(1);
    if( IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) ) movePlayer(-1);
}

Hit Raycaster::castRay( double deltaAngle ) {
    const double eps = 1e-20;
    double alpha = deltaAngle + angle;
    if( alpha >= 2*PI ) alpha -= 2*PI;
    if( alpha < 0 ) alpha += 2*PI;

    double deltaRayX = sin(alpha) == 0 ? eps : 1 / sin(alpha);
    double deltaRayY = cos(alpha) == 0 ? eps : 1 / cos(alpha);

    deltaRayX = fabs(deltaRayX);
    deltaRayY = fabs(deltaRayY);

    int axisX = int(pos.x);
    int axisY = int(pos.y);
    int deltaAxisX = cos(alpha) >= 0 ? 1 : -1;
    int deltaAxisY = sin(alpha) >= 0 ? 1 : -1;

    bool last;
    double distX = 0;
    double distY = 0;
    distX = deltaAxisY == 1 ? (float)axisY+1-pos.y : pos.y-(float)axisY; distX *= deltaRayX;
    distY = deltaAxisX  == 1 ? (float)axisX+1-pos.x : pos.x-(float)axisX; distY *= deltaRayY;

    while( map[ axisY ][ axisX ] == 0 ) {
        if( distX > distY ) {
            // we try to to collide with Y axis
            distY += deltaRayY;
            axisX += deltaAxisX;
            last = 0;
        } else {
            distX += deltaRayX;
            axisY += deltaAxisY;
            last = 1;
        }
        // Draw "visited" squares by ray
        // DrawRectangle(axisX*30+5, axisY*30+5, 20, 20, PURPLE);
    }

    Hit ret;
    ret.mapX = axisX;
    ret.mapY = axisY;
    ret.side = last;

    // correct when ray goes in dir of negative coordinate ( any )
    axisX += deltaAxisX < 0 ? -deltaAxisX : 0;
    axisY += deltaAxisY < 0 ? -deltaAxisY : 0;
    if( last ) {
        ret.x = ((float)axisY-pos.y) / ( tan(alpha) == 0 ? eps : tan(alpha) ) + pos.x;
        ret.y = axisY;
        ret.part = ret.x - floorf(ret.x);
    } else {
        ret.x = axisX;
        ret.y = ((float)axisX-pos.x) * tan(alpha) + pos.y;
        ret.part = ret.y - floorf(ret.y);
    }

    return ret;
}

void Raycaster::draw() {
    int screenWidth  = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    Vector2 dir = {cos(angle), sin(angle)}; // plane parallel to direction of looking


    // ========== SKYBOX ===========
    DrawTexture(skyBox, 0, 0, WHITE);
    // ========= FLOOR & CEIL CASTING =========
    int playerHeight = screenHeight/2;
    const float ufff = 1 / cos(fov/2);
    bool sneed[1200]={0};
    for( int p = screenHeight/2 - 1; p > 0 ; p-- ) {
        float rowDist = (float)playerHeight / (float)p;
        Vector2 step;
        Vector2 mpos = {pos.x,pos.y};

        mpos.x += rowDist * cos(angle+fov/2) * ufff;
        mpos.y += rowDist * sin(angle+fov/2) * ufff;

        step.x = 2 * tan(fov/2)*rowDist*cos(PI/2 - angle); // multiplyinf by 2... took too long to find that shit
        step.y = 2 * tan(fov/2)*rowDist*sin(PI/2 - angle)*(-1);
        step.x /= screenWidth;
        step.y /= screenWidth;
        for(int x = 0; x < screenWidth ; x++ ) {
            if( sneed[x] ) continue;
            int px = int(mpos.x);
            int py = int(mpos.y);
//            if( map[py][px] != 0 ) {
//                sneed[x] = 1;
//                continue;
//            }
//            if( (px >= mapWidth) || (px < 0) || (py >= mapHeight) || (py < 0) ) continue;

            int flexid = floor[py][px];
            int ceilid = ceiling[py][px];
            flexid = ceilid = 5;

            int tx = (float)(textures[flexid].width) * (mpos.x - (float)px); //tx %= 16;
            int ty = (float)(textures[flexid].height) * (mpos.y - (float)py); //ty %= 16;

            mpos.x += step.x;
            mpos.y += step.y;

            DrawPixel(x, playerHeight+p, textures[flexid].pixel[ty][tx]);
//            DrawRectangle(x,playerHeight+p,2,2,textures[flexid].pixel[ty][tx]);
//            DrawPixel(x, playerHeight-p, textures[ceilid].pixel[ty][tx]);
//            DrawPixel(30*mpos.x, 30*mpos.y, PINK);
        }
    }

    // ========= WALL CASTING ================
    for (int x = 0; x < screenWidth; x++) {
        double rayAngle = fov/2 - (double)x * fov / (double)screenWidth;
        auto ray = castRay(rayAngle);
        Vector2 vectorToHit = {ray.x-pos.x, ray.y-pos.y};

        double perpDist = vectorToHit.x * dir.x + vectorToHit.y * dir.y; // just dot prod, we dont divide because dir of lenght 1
        perpDist = fabs(perpDist);

        double lineHeight = screenHeight / perpDist;
        int startX = x, startY = screenHeight/2 - lineHeight/2;
        int endX = x, endY = screenHeight/2 + lineHeight/2;

        Color col= colors[map[ray.mapY][ray.mapX]];

        int textureId = map[ray.mapY][ray.mapX];
        int texSide = textures[textureId].width; // assuming they're square, cause they won`t be other shapes obviously
        int texPart = int(texSide*ray.part);
        double pixelHeight =  lineHeight / texSide;
        for(int p=0;p<texSide;p++) {
            DrawLine(
                    startX,
                    startY + p*pixelHeight,
                    endX,
                    startY +(p+1)*pixelHeight,
                    textures[textureId].pixel[texPart][p]
                    );
        }
        /* drawing using raylib textures (bad)
        Rectangle source = {int(texSide*ray.part), 0, 1, texSide};
        Rectangle dest = {x,startY, 1, lineHeight};

        Color cols = WHITE;
        cols.a = ray.side ? 100 : 255;
        DrawTexturePro(textures[textureId], source, dest, {0,0}, 0.0f, cols);*/
    }

//    DrawLine(pos.x*30,pos.y*30,(pos.x+30*cos(angle))*30, (pos.y+sin(angle)*30)*30, WHITE);
//    DrawLine(pos.x*30,pos.y*30,(pos.x+30*cos(angle+fov/2))*30, (pos.y+sin(angle+fov/2)*30)*30, BLACK);
//    DrawLine(pos.x*30,pos.y*30,(pos.x+30*cos(angle-fov/2))*30, (pos.y+sin(angle-fov/2)*30)*30, WHITE);
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
    int numOfRays = 200;
    for(int i=0;i<numOfRays;i++) {
        auto rayFromMe = castRay(fov/2 - (float)i * fov/(float)numOfRays);
        DrawLine(px, py, int(rayFromMe.x * side), int(rayFromMe.y * side), WHITE);
    }

    DrawText(TextFormat("Position: %04.04f %04.04f", pos.x, pos.y), 720,10,22, WHITE);
    DrawText(TextFormat("Angle: %04.04f ( %04.02f deg )", angle, (360*angle/(2*PI))), 720,30,22, WHITE);
}


void Raycaster::showDebug() {
    DrawText(TextFormat("FPS: %i", GetFPS()), 3,10,22, WHITE); // fps
    DrawText(TextFormat("dTime: %.5f", GetFrameTime()), 3,30,22, WHITE); // delta time
    DrawText(TextFormat("mouse (x,y): (%i, %i) ", GetMouseX(), GetMouseY()), 3,50,22, WHITE); // mouse pos
}
#endif //RAYCASTING_RAYCASTER_H