#pragma once
#include "raylib.h"

class Laser {
    private:
        Vector2 position;
        int speed;

    public:
        Laser(Vector2, int);
        void draw();
        void update();
        bool active;
        Rectangle GetRect();
};