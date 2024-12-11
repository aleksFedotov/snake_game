#pragma once
#include <raylib.h>
#include  <raymath.h>
#include <deque>


class Snake
{
private:
    int cellSize;
public:
    Snake(int cellSize);
    std::deque<Vector2> body;
    void Draw();
    void Update();
    Vector2 direction;
};

