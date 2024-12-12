#pragma once
#include <raylib.h>
#include  <raymath.h>
#include <deque>


class Snake
{
private:
    int cellSize;
public:
    Snake();
    std::deque<Vector2> body;
    void Draw();
    void Update();
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    bool isNotMovingUp();
    bool isNotMovingDown();
    bool isNotMovingRight();
    bool isNotMovingLeft();
    void setCellSize(int cellSize);
    bool addSegment = false;
    Vector2 direction;
};

