
#include "snake.hpp"
#include "colors.hpp"


Snake::Snake()
{
    
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
    Vector2 newHead = Vector2Add(body[0], direction);
    body.push_front(newHead);

    if(addSegment) 
    {
        addSegment = false;
    } 
    else 
    {
        body.pop_back();
    }
}

void Snake::MoveUp()
{
    direction = {0,-1};
}

void Snake::MoveDown()
{
    direction = {0,1};
}

void Snake::MoveRight()
{
    direction = {1,0};
}

void Snake::MoveLeft()
{
    direction = {-1,0};
}

bool Snake::isNotMovingUp()
{
    if(direction.y != -1)
    {
        return true;
    }
    return false;
}

bool Snake::isNotMovingDown()
{
    if(direction.y != 1)
    {
        return true;
    }
    return false;
}

bool Snake::isNotMovingRight()
{
    if(direction.x != 1)
    {
        return true;
    }
    return false;
}

bool Snake::isNotMovingLeft()
{
    if(direction.x != -1)
    {
        return true;
    }
    return false;
}

void Snake::setCellSize(int cellSize)
{
    this -> cellSize = cellSize;
}
