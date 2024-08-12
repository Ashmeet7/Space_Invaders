#pragma once
#include "block.hpp"
#include <vector>

class Obstacle{
    private:

    public:
        Vector2 position;
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
        Obstacle(Vector2 position);
        void draw();
};