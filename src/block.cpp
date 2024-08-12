#include "block.hpp"

Rectangle Block::GetRect()
{
    return Rectangle({position.x, position.y, 3, 3});
}

Block::Block(Vector2 position)
{
    this -> position = position;
}

void Block::draw() {
    DrawRectangle(position.x, position.y, 3, 3, {243,216,63,255});
}