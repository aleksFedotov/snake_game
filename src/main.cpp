#include <raylib.h>
#include "colors.hpp"
#include "food.hpp"
#include "snake.hpp"


int main() 
{
    int cellSize = 30;
    int cellCount = 25;

    const int screenWidth  = cellSize * cellCount;
    const int screenHeight = cellSize * cellCount;
    int fps = 60;



    InitWindow(screenWidth,screenHeight, "Snake Game");
    SetTargetFPS(fps);

    Food food = Food(cellSize, cellCount);
    Snake snake = Snake(cellSize);
;
    while(!WindowShouldClose())
    {   
        BeginDrawing();

        ClearBackground(green);
        food.Draw();
        snake.Draw();
        snake.Update();
        

        EndDrawing();
    }

    CloseWindow();

}