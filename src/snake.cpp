
#include "snake.hpp"
#include "colors.hpp"


Snake::Snake()
{
    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {1,0};
    head = body[0];
}

void Snake::Draw()
{   
    
    for (unsigned int i = 0; i < body.size(); i++)
    {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = Rectangle{offset +  x*cellSize,offset + y *cellSize, (float)cellSize, (float)cellSize};

        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
    }
    
}

void Snake::Update()
{
    Vector2 newHead = Vector2Add(head, direction);
    body.push_front(newHead);
    head = newHead;

    if(addSegment) 
    {
        addSegment = false;
    } 
    else 
    {
        body.pop_back();
    }
}

void Snake::Reset()
{
    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {0,1};
    head = body[0];
}


bool Snake::isNotMovingUp()
{
    return direction.y != -1;
}

bool Snake::isNotMovingDown()
{
    return direction.y != 1;
}

bool Snake::isNotMovingRight()
{
    return direction.x != 1;
}

bool Snake::isNotMovingLeft()
{
    return direction.x != -1;
}

bool Snake::IsOutOfBounds(int cellCount)
{
   return head.x < 0 || head.y < 0 || head.x >= cellCount || head.y >= cellCount;
}

void Snake::SetDirection(Vector2 newDirection)
{
    direction = newDirection;
}

void Snake::Initialize(int cellSize, int offSet)
{
    this -> cellSize = cellSize;
    this -> offset = offSet;
}
