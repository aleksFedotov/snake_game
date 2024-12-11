
#include "snake.hpp"
#include "colors.hpp"


Snake::Snake(int cellSize)
{
    this -> cellSize = cellSize;
    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {1,0};
}

void Snake::Draw()
{   
    
    for (unsigned int i = 0; i < body.size(); i++)
    {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = Rectangle{x*cellSize, y *cellSize, (float)cellSize, (float)cellSize};

        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
    }
    
}

void Snake::Update()
{
    body.pop_back();
    Vector2 newHead = Vector2Add(body[0], direction);
    body.push_front(Vector2{newHead.x, newHead.y});
}
