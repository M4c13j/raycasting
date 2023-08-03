#ifndef RAYCASTING_BTEXTURES_CPP
#define RAYCASTING_BTEXTURES_CPP
#include "raylib.h"
#include <iostream>

struct BTexture {
    int width = 16;
    int height = 16;
    Color pixel[16][16];
    void loadFromImage(Image &img); // MUST BE the same dimentions as pixel;
};

void BTexture::loadFromImage(Image &img) {
    if( img.width != 16 || img.height != 16 ) {
        std::cout << "TEXTURE WRONG SIZE\n";
        return;
    }

    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
            pixel[i][j] = GetImageColor(img,i,j);
}

#endif //RAYCASTING_PLAYER_H
