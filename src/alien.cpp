#include "alien.hpp"
#include <iostream>

Texture2D Alien::alienimages[3] = {};

Alien::Alien(int type, Vector2 position) {
    this -> type = type;
    this -> position = position;

    if(alienimages[type-1].id == 0) {
        switch (type)
        {
            case 1:
                alienimages[0]  = LoadTexture("Graphics/alien_1.png");
                break;
            case 2:
                alienimages[1] = LoadTexture("Graphics/alien_2.png");
                break;
            case 3:
                alienimages[2] = LoadTexture("Graphics/alien_3.png");
                break;
            default:
                alienimages[0]  = LoadTexture("Graphics/alien_1.png");
                break;
        }
    }    
}

void Alien::draw() {
    DrawTexture(alienimages[type-1],position.x, position.y, WHITE);
}

int Alien::gettype() {
    return type;
}

Rectangle Alien::GetRect()
{
    return Rectangle({position.x,position.y,(float)alienimages[type-1].width,(float)alienimages[type-1].height});
}

void Alien::unloadImages() {
    for(int i = 0; i < 4; i++) {
        UnloadTexture(alienimages[i]);
    }
}

void Alien::update(int direction) {
    position.x += direction;
}