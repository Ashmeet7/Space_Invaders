#pragma once 
#include "raylib.h"

class Alien{
    public:
        Alien(int type, Vector2 position);
        static Texture2D alienimages[3];
        static void unloadImages();
        int type;
        Vector2 position;
        void draw();
        void update(int direction);
        int gettype();
        Rectangle GetRect();
};