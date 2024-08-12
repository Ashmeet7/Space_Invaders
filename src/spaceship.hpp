#pragma once
#include "raylib.h"
#include "laser.hpp"
#include <vector>

class Spaceship{
    private:
        Texture2D image;
        Vector2 position;    
        double lastfiretime;
        Sound lasersound;
    public:
        std::vector<Laser> lasers;
        Spaceship();
        ~Spaceship();
        void draw();
        void moveleft();
        void moveright();
        void firelaser();
        Rectangle GetRect();
        void Reset();
};