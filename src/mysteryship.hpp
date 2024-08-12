#pragma once
#include "raylib.h"

class MysteryShip{
    private:
        Texture2D image;
        Vector2 position;
        int speed;

    public:
        MysteryShip();
        ~MysteryShip();
        void update();
        void draw();
        void spawn();
        bool alive;
        Rectangle GetRect();
};