#include "mysteryship.hpp"

Rectangle MysteryShip::GetRect()
{
    if(alive) {
        return Rectangle({position.x, position.y, (float)image.width, (float)image.height});
    }
    else {
        return Rectangle({position.x, position.y, 0, 0});
    }
}

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

void MysteryShip::spawn() {
    position.y = 40;
    int side = GetRandomValue(0,1);

    if(side == 0) {
        position.x = 10;
        speed = 3;
    }
    else {
        position.x = GetScreenWidth()-10;
        speed = -3;
    }
    alive = true;
}

void MysteryShip::draw() {
    if(alive)
        DrawTexture(image, position.x, position.y, WHITE);
}

void MysteryShip::update() {
    if(alive) {
        position.x += speed;
        if(position.x < 10 || position.x>GetScreenWidth()-image.width-10) {
            alive = false;
        }
    }
}