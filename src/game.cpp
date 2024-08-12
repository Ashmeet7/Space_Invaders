#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
    refer_alien_image = LoadTexture("Graphics/alien_1.png");
    music = LoadMusicStream("Sounds/music.ogg");
    explosionsound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game() {
   Alien::unloadImages(); 
   UnloadMusicStream(music);
   UnloadSound(explosionsound);
   UnloadTexture(refer_alien_image);
}

void Game::GameOver()
{
    run = false;
}

void Game::InitGame() {
    obstacles = createobstacles();
    aliens = createaliens();
    aliendirection = 1;
    timeLaserlastFire = 0.0;
    timelastspawnmystery = 0.0;
    mysteryInterval = GetRandomValue(10,20);
    lives = 3;
    score = 0;
    highscore = loadhighscore();
    run = true;   
}


void Game::GameReset() {
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    mystery.alive = false;
    ResumeMusicStream(music);
}

void Game::checkforhighscore()
{
    if(score > highscore) {
        highscore = score;
        savehighscoretexttofile(highscore);
    }
}

void Game::savehighscoretexttofile(int highs)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
       highscoreFile << highs; 
       highscoreFile.close();
    }
    else {
        std::cerr << "can not open highscore file" << std::endl;
    }
}

int Game::loadhighscore()
{
    int loadedscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile >> loadedscore;
        highscoreFile.close();
    }
    else {
        std::cerr << "can not open highscore file" << std::endl;
    }
    return loadedscore;
}


void Game::deleteinactivelaser() {
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if(it ->active == false) {
            it = spaceship.lasers.erase(it);
        }
        else {
            ++it;
        }
    }

    for(auto it = alienLasers.begin(); it != alienLasers.end();) {
        if(it -> active == false) {
            it = alienLasers.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::update() {
    if(run) {
        if(aliens.empty()) {
            GameOver();
        }

        if(!aliens.empty()) {
            for(auto& alien : aliens) {
                if(alien.position.y+refer_alien_image.height >= 740) {
                    GameOver();
                }
            }
        }

        double currenttime = GetTime();
        if(currenttime - timelastspawnmystery > mysteryInterval) {
            mystery.spawn();
            timelastspawnmystery = GetTime();
            mysteryInterval = GetRandomValue(10,20);
        }

        for(auto &laser: spaceship.lasers) {
            laser.update();
        }
        alienshootlaser();
        for(auto &laser: alienLasers) {
            laser.update();
        }
        movealien();
        deleteinactivelaser();
        mystery.update();

        checkforcollisons();
    }
    else {
        PauseMusicStream(music);
        if(IsKeyDown(KEY_ENTER)) {
            GameReset();
            InitGame();
        }
    }
}

void Game::draw() {
    spaceship.draw();
    for(auto &laser : spaceship.lasers) {
        laser.draw();
    }

    for(auto &obstacle: obstacles) {
        obstacle.draw();
    }

    for(auto &alien: aliens) {
        alien.draw();
    }

    for(auto& laser: alienLasers) {
        laser.draw();
    }

    mystery.draw();
}

void Game::handleinput() {

    if(run) {
        if(IsKeyDown(KEY_LEFT)) {
            spaceship.moveleft();
        }
        else if(IsKeyDown(KEY_RIGHT)) {
            spaceship.moveright();
        }
        else if(IsKeyDown(KEY_UP)) {
            spaceship.firelaser();
        }
    }
}

void Game::checkforcollisons()
{
    for(auto &laser : spaceship.lasers) {
        // spaceship laser and alien collison
        auto it = aliens.begin();
        while(it != aliens.end()) {
            if(CheckCollisionRecs(laser.GetRect(), it->GetRect())) {

                PlaySound(explosionsound);
                if(it->type == 1) {
                    score += 100;
                }
                else if(it -> type == 2) {
                    score += 200;
                }
                else if(it -> type == 3) {
                    score += 300;
                }

                checkforhighscore();
                it = aliens.erase(it); 
                laser.active = false;
            }
            else {
                ++it;
            }
        }

        //spaceship laser and obstacle collison
        for(auto &obs : obstacles) {
            auto it = obs.blocks.begin();

            while(it != obs.blocks.end()) {
                if(CheckCollisionRecs(it -> GetRect(), laser.GetRect())) {
                    it = obs.blocks.erase(it);
                    laser.active = false;
                }
                else {
                    ++it;
                }
            } 
        }

        //spaceship laser and mystery ship collison
        if(CheckCollisionRecs(laser.GetRect(), mystery.GetRect())) {
            PlaySound(explosionsound);
            laser.active = false;
            mystery.alive = false;
            score += 500;
            checkforhighscore();
        }
    }


    for(auto& laser : alienLasers) {

        //alien laser and spaceship collison
        if(CheckCollisionRecs(laser.GetRect(), spaceship.GetRect())) {
            laser.active = false;
            lives--;
            if(lives == 0) {
                GameOver();
            }
        }

        for(auto& obs : obstacles) {
            auto it = obs.blocks.begin();
            while(it != obs.blocks.end()) {
                if(CheckCollisionRecs(laser.GetRect(), it->GetRect())) {
                    it = obs.blocks.erase(it);
                    laser.active = false;
                }
                else {
                    ++it;
                }
            }
        }
    }

    for(auto &alien : aliens) {
        for(auto& obs : obstacles) {
            auto it = obs.blocks.begin();

            while(it != obs.blocks.end()) {
                if(CheckCollisionRecs(it -> GetRect(), alien.GetRect())) {
                    it = obs.blocks.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(alien.GetRect(), spaceship.GetRect())) {
            GameOver();
        }
    }
}

std::vector<Obstacle> Game::createobstacles() {
    int obstaclwidth = Obstacle::grid[0].size()*3;
    float gap = (GetScreenWidth()-(obstaclwidth*4))/5;
    for(int i = 0; i < 4; i++) {
        float offsetx = (i+1)*gap + i*obstaclwidth;
        obstacles.push_back(Obstacle({offsetx,float(GetScreenHeight()-200)}));
    }

    return obstacles;
}

std::vector<Alien> Game::createaliens() {
    std::vector<Alien> aliens;
    int type = 1;

    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 11; col++) {
            if(row == 0) type = 3;
            else if(row == 1 || row ==2) type = 2;
            else type = 1;

            float x = 75 + col*55;
            float y = 90 + row*55;          

            aliens.push_back(Alien(type,{x,y}));
        }
    }
    return aliens;
}

void Game::movealien() {
    for(auto &alien : aliens) {
        if(alien.position.x + alien.alienimages[alien.type-1].width + 25 > GetScreenWidth()) {
            aliendirection = -1;
            movealiendown(4);
        }
        else if(alien.position.x < 25){
            aliendirection = 1;
            movealiendown(4);
        }
        alien.update(aliendirection);
    }
}

void Game::movealiendown(int dir) {
    for(auto& alien : aliens) {
        alien.position.y += dir;
    }
}

void Game::alienshootlaser() {

    double currenttime = GetTime();

    if(currenttime-timeLaserlastFire > alienshootinterval && !aliens.empty()) {
        int randvalue = GetRandomValue(0, aliens.size()-1);
        Alien& alien = aliens[randvalue];
        alienLasers.push_back(Laser
        ({alien.position.x+alien.alienimages[alien.type-1].width/2, alien.position.y+alien.alienimages[alien.type-1].height},6));    
        timeLaserlastFire = GetTime();
    }
}