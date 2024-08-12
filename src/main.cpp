#include <iostream>
#include "raylib.h"
#include "game.hpp"
#include <string>

std::string formatscore(int number, int width) {
    std::string numbertext = std::to_string(number);
    int leadingzeroes = width-numbertext.length();
    return numbertext = std::string(leadingzeroes,'0')+numbertext;
}

const int WIDHTH = 750;
const int HEIGHT = 700;
Color grey = {29,29,27,255};
Color yellow = {243,216,63,255};
int offset = 50;
const char* title = "space invaders";

int main(int argc, char** argv) {

    InitWindow(WIDHTH+offset,HEIGHT+2*offset,title);
    InitAudioDevice();
    SetTargetFPS(60);
    Game game;
    Font font = LoadFont("Font/monogram.ttf");
    Texture2D Spaceshipimage = LoadTexture("Graphics/spaceship.png");

    while(!WindowShouldClose()) {
        UpdateMusicStream(game.music);
        ClearBackground(grey);
        game.update();
        game.handleinput();

        BeginDrawing();

        DrawRectangleRoundedLines({10,10,780,780},0.10f,20,2,yellow);
        DrawLineEx({25,730}, {775,730}, 3, yellow);

        if(game.run) {
            DrawTextEx(font, "LEVEL 01", {570,740},34,2,yellow);
        }
        else {
            DrawTextEx(font, "GAME OVER", {570,740},34,2,yellow);
        }

        float x = 50.0;
        for(int i = 0; i < game.lives; i++) {
            DrawTextureV(Spaceshipimage, {x,745}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50,15}, 34, 2, yellow);
        std::string scoretext = formatscore(game.score, 5);
        DrawTextEx(font, scoretext.c_str(), {50,40}, 34, 2, yellow);

        DrawTextEx(font,"HIGH-SCORE", {570,15}, 34,2,yellow);
        std::string highscoretext = formatscore(game.highscore, 5);
        DrawTextEx(font,highscoretext.c_str(), {655,40,},34,2,yellow);

        game.draw();

        EndDrawing();
    }
    UnloadTexture(Spaceshipimage);

    CloseWindow();
    return 0;
}