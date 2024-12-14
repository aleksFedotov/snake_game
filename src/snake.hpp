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
    Snake(int startX, int startY, int length);
    std::deque<Vector2> body;
    Vector2 head;
    void Draw();
    void Update();
    void Reset();
    bool isNotMovingUp();
    bool isNotMovingDown();
    bool isNotMovingRight();
    bool isNotMovingLeft();
    bool IsOutOfBounds(int cellCount);
    void SetDirection(Vector2 newDirection);
    void Initialize(int cellSize,int offSet);
    void Grow();
    bool addSegment = false;
    Vector2 direction;
};

