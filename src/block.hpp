#pragma once
#include "raylib.h"

class Block{
    private:
        Vector2 position;
        bool isactive;

    public:
        Block(Vector2 position);
        void draw();
        void update();
        Rectangle GetRect();
};