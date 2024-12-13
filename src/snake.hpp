#pragma once
#include <raylib.h>
#include  <raymath.h>
#include <deque>


class Snake
{
private:
    int cellSize;
    int offset;
public:
    Snake();
    std::deque<Vector2> body;
    Vector2 head;
    void Draw();
    void Update();
    void Reset();
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    bool isNotMovingUp();
    bool isNotMovingDown();
    bool isNotMovingRight();
    bool isNotMovingLeft();
    void setCellSize(int cellSize);
    void setOffset(int offSet);
    bool addSegment = false;
    Vector2 direction;
};

