#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth()-image.width)/2;
    position.y = GetScreenHeight()-image.height-110;
    lastfiretime = 0.0;
    lasersound = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship() {
    UnloadTexture(image);
    UnloadSound(lasersound);
}

void Spaceship::firelaser() {
    if(GetTime()-lastfiretime >= 0.35) {
        lasers.push_back(Laser({position.x+image.width/2,position.y},-6));
        lastfiretime = GetTime();
        PlaySound(lasersound);
    }
}

Rectangle Spaceship::GetRect()
{
    return Rectangle({position.x,position.y,(float)image.width,(float)image.height});
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth()-image.width)/2;
    position.y = GetScreenHeight()-image.height-110;
    lasers.clear();
}


void Spaceship::draw() {
    DrawTextureV(image, position,WHITE);
}

void Spaceship::moveleft() {
    position.x -= 7;
    if(position.x < 25) 
        position.x = 25;
}

void Spaceship::moveright() {
    position.x += 7;
    if(position.x > GetScreenWidth()-image.width-25) 
        position.x = GetScreenWidth()-image.width-25;
}
