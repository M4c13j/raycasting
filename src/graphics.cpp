#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "../include/raylib.h"
#include "constants.hpp"
#include <math.h>
#include <string>
#include <vector>

class Graphics {
public:
    Texture2D images[16];
    Texture2D textures[16];
    
    void LoadTextures();

};

void Graphics::LoadTextures() {
    Image image;
    Texture2D texture;

    image = LoadImage("../img/skybox.png");
    texture = LoadTextureFromImage( image );

    images[0] =  texture ;
    UnloadImage( image );
}

#endif