#include "snake.hpp"
#include "colors.hpp"

// Constructor to initialize the snake at a specific starting position and with a specified length
Snake::Snake(int startX, int startY, int length)
{
    // Initialize the snake's body with given length
    for (int i = 0; i < length; i++) 
    {
        body.push_back(Vector2{(float)(startX - i), (float)startY});  // Add segments to the body
    }
    direction = {1, 0};  // Set the initial direction of the snake (moving to the right)
    head = body[0];  // The head is the first element in the body
}

// Method to draw the snake on the screen
void Snake::Draw()
{   
    // Loop through each segment of the snake's body and draw it
    for (unsigned int i = 0; i < body.size(); i++)
    {
        float x = body[i].x;
        float y = body[i].y;
        // Create a rectangle for each segment with the correct position and size
        Rectangle segment = Rectangle{offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};

        // Draw the head with a rounded rectangle and a distinct color (lime green)
        if (i == 0)
            DrawRectangleRounded(segment, 0.5, 6, limeGreen); // Head color
        else
            DrawRectangleRounded(segment, 0.5, 6, darkGreen); // Body color
    }
}

// Update the snake's movement based on the direction
void Snake::Update()
{
    // Calculate the new head position by adding the direction to the current head position
    Vector2 newHead = Vector2Add(head, direction);
    body.push_front(newHead);  // Add the new head to the front of the body
    head = newHead;  // Update the head to the new head

    // If the snake is supposed to grow, add a segment, otherwise, remove the last segment
    if (addSegment) 
    {
        addSegment = false;
    } 
    else 
    {
        body.pop_back();  // Remove the tail segment to maintain the snake's length
    }
}

// Reset the snake's position and direction to the initial state
void Snake::Reset()
{
    // Set the initial body of the snake to a predefined starting position
    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {0, 1};  // Set the initial direction (moving down)
    head = body[0];  // The head is still the first segment
}

// Check if the snake is not moving upward
bool Snake::isNotMovingUp()
{
    return direction.y != -1;  // True if not moving up (y-direction is not -1)
}

// Check if the snake is not moving downward
bool Snake::isNotMovingDown()
{
    return direction.y != 1;  // True if not moving down (y-direction is not 1)
}

// Check if the snake is not moving to the right
bool Snake::isNotMovingRight()
{
    return direction.x != 1;  // True if not moving right (x-direction is not 1)
}

// Check if the snake is not moving to the left
bool Snake::isNotMovingLeft()
{
    return direction.x != -1;  // True if not moving left (x-direction is not -1)
}

// Check if the snake has moved out of bounds of the game grid
bool Snake::IsOutOfBounds(int cellCount)
{
   // Check if the head is outside the valid grid area (0 to cellCount - 1)
   return head.x < 0 || head.y < 0 || head.x >= cellCount || head.y >= cellCount;
}

// Set the snake's direction, ensuring it doesn't move in the opposite direction
void Snake::SetDirection(Vector2 newDirection)
{
    // Prevent the snake from reversing direction (e.g., not moving left if already moving right)
    if ((direction.x + newDirection.x != 0) || (direction.y + newDirection.y != 0)) 
    {
        direction = newDirection;  // Update the direction if the new direction is not the opposite
    }
}

// Initialize the snake with cell size and offset (for screen positioning)
void Snake::Initialize(int cellSize, int offSet)
{
    this->cellSize = cellSize;  // Set the cell size for drawing
    this->offset = offSet;      // Set the offset for positioning on the screen
}

// Enable the snake to grow by adding a new segment to its body
void Snake::Grow()
{
    addSegment = true;  // Flag to add a new segment on the next update
}
