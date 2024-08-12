#pragma once 
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
class Game {
    private:
        Spaceship spaceship;
        void deleteinactivelaser();
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        std::vector<Obstacle> createobstacles();
        std::vector<Alien> createaliens();
        std::vector<Laser> alienLasers;
        void alienshootlaser();
        void movealiendown(int);
        void movealien();
        int aliendirection = 1;
        constexpr static float alienshootinterval = 0.35;
        float timeLaserlastFire;
        MysteryShip mystery;
        float mysteryInterval;
        float timelastspawnmystery;
        void GameOver();
        void InitGame();
        void GameReset();
        void checkforhighscore();
        void savehighscoretexttofile(int);
        int loadhighscore();
        Sound explosionsound;
        Texture2D refer_alien_image;
    public:
        Game();
        ~Game();
        void draw();
        void update();
        void handleinput();
        void checkforcollisons();
        int lives;
        int score;
        int highscore;
        bool run = true;
        Music music;
};