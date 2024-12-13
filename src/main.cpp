#include <raylib.h>
#include "colors.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "game.hpp"


// Global variable to track the time of the last update.
double lastUpdateTime = 0;

// Function to determine if an event should be triggered based on the interval.
bool EventTriggered(double interval) 
{
   double currentTime = GetTime();  // Get the current time.
   if(currentTime - lastUpdateTime >= interval)  // Check if the interval has passed.
   {
      lastUpdateTime = currentTime;  // Update the last update time.
      return true;  // Event triggered.
   }
   return false;  // Event not triggered.
}

int main() 
{
    int cellSize = 30;
    int cellCount = 25;
    int offset = 75;

    const int screenWidth  = 2*offset + cellSize * cellCount;
    const int screenHeight = 2*offset + cellSize * cellCount;
    int fps = 60;

    InitWindow(screenWidth,screenHeight, "Snake Game");
    SetTargetFPS(fps);


    Game game = Game(cellSize,cellCount,offset);
;
    while(!WindowShouldClose())
    {   
        BeginDrawing();
        game.HandleInput();
        if(EventTriggered(0.2))
        {
            game.Update();
        }

    
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset-5, (float)offset - 5, (float)cellSize*cellCount +10,(float)cellSize*cellCount +10}, 5, darkGreen);
        DrawText("Retro Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();
     

        EndDrawing();
    }

    CloseWindow();

}