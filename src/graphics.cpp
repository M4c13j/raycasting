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
    int imFiles = 1 , textFiles = 1;
    std::string imagesFiles[] = {
        "../img/skybox.png"
    };
    std::string texturesFiles[] = {
        "../img/wood.png"
    };

    Image image;
    Texture2D texture;
    
    image = LoadImage("../img/wood.png");
    texture = LoadTextureFromImage( image );

    textures[ 0 ] = texture;
    UnloadImage( image );
//     for( int i=0;i<imFiles;i++ ) {
//         image = LoadImage( imagesFiles[i].c_str() );
//         texture = LoadTextureFromImage( image );

//         images[ i ] = texture;
//         UnloadImage( image );
//     }

//     for( int i=0;i<textFiles;i++ ) {
//         image = LoadImage( texturesFiles[i].c_str() );
//         texture = LoadTextureFromImage( image );

//         textures[ i ] = texture;
//         UnloadImage( image );
//     }
}

#endif