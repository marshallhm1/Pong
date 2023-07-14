#include <raylib.h>
#include <iostream>
#include <string>
//Sources
#include "Ball.h"
#include "Paddle.h"
#include "Button.h"
using namespace std;

// Colors
Color Ocean = Color{255, 0, 0, 1};
// Background
Color Royal_Blue = Color{65, 105, 225, 255};
// Middle Circle
Color Light_Green = Color{0, 168, 107, 255};

//Game Variables
int player_score, cpu_score, high_score = 0;
bool gameStarted, gameOver, gamePaused = false;
int difficulty = 1; // Default Difficulty (Easy)
int scoreLimit = 10; // Default score limit: 10

//Class Declarations
Ball ball;
Paddle player;
CpuPaddle cpu;

//Create Title Screen
void DrawTitleScreen(Button& startButton, Button& difficultyButton, Button& scoreLimitButton)
{
    const int screenWidth = GetScreenWidth();

    ClearBackground(Royal_Blue);
    DrawText("Pong", screenWidth / 2 - MeasureText("Pong", 140) / 2, 200, 140, LIGHTGRAY);
    DrawText("Programmed By Marshall in Houston", screenWidth / 2 - MeasureText("Programmed By Marshall in Houston", 13) / 2, 25, 13, LIGHTGRAY);
    startButton.Draw();
    difficultyButton.Draw();
    scoreLimitButton.Draw();
}

//Create Game Over Screen
void DrawGameOverScreen(Button& restartButton)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    ClearBackground(Royal_Blue);
    DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 80) / 2, screenHeight / 2 - 80, 80, LIGHTGRAY);
    DrawText("Winner: ", screenWidth / 2 - MeasureText("Winner: ", 20) / 2, screenHeight / 2, 20, LIGHTGRAY);
    if (player_score >= scoreLimit)
    {
        DrawText("Player", screenWidth / 2 - MeasureText("Player", 40) / 2, screenHeight / 2 + 40, 40, LIGHTGRAY);
    }
    else
    {
        DrawText("CPU", screenWidth / 2 - MeasureText("CPU", 40) / 2, screenHeight / 2 + 40, 40, LIGHTGRAY);
    }
    DrawText(("High Score: " + to_string(high_score)).c_str(), screenWidth / 2 - MeasureText(("High Score: " + to_string(high_score)).c_str(), 20) / 2, 600, 20, LIGHTGRAY); // Display high score
    restartButton.Draw();
}

//Adjust Game Settings
void UpdateTitleScreen(Button& startButton, Button& difficultyButton, Button& scoreLimitButton)
{
    if (startButton.IsPressed())
    {
        gameStarted = true;
    }

    if (difficultyButton.IsPressed())
    {
        difficulty = (difficulty % 3) + 1; // Cycle through 3 difficulty levels (1, 2, 3)

        // Update difficulty button text based on the selected difficulty level
        switch (difficulty)
        {
            case 1:
                difficultyButton.text = "Difficulty: Easy";
                player.speed = 6;
                cpu.speed = 3.5;
                ball.speed_x = 10;
                ball.speed_y = 10;
                break;
            case 2:
                difficultyButton.text = "Difficulty: Medium";
                player.speed = 9;
                cpu.speed = 5.5;
                ball.speed_x = 10;
                ball.speed_y = 10;
                break;
            case 3:
                difficultyButton.text = "Difficulty: Hard";
                player.speed = 13;
                cpu.speed = 9;
                ball.speed_x = 13;
                ball.speed_y = 13;
                break;
        }
    }

    // Check for scoreLimitButton press outside the difficultyButton condition
    if (scoreLimitButton.IsPressed())
    {
        scoreLimit = (scoreLimit % 20) + 1; // Cycle through 20 score limits (1-20)

        // Update score limit button text based on the selected score limit
        scoreLimitButton.text = "Score Limit: " + to_string(scoreLimit);
    }
}

//Update Game Loop
void UpdateGameOverScreen(Button& restartButton)
{
    if (restartButton.IsPressed())
    {
        // Reset game state
        int player_score, cpu_score = 0;
        bool gameStarted, gameOver = false;
    }
}

//Main
int main()
{
    //Create Game Window and Raylib constants
    cout << "Starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong v1.0");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    // Default If Difficulty Not Pressed (Easy)
    player.speed = 6;
    cpu.speed = 3.5;
    ball.speed_x = 7;
    ball.speed_y = 7;
    player.width = 25;
    player.height = 150;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    cpu.height = 150;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;

    // Buttons
    Button startButton(
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 30), 200, 50},
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 30), 200, 50},
            Ocean, "Start");
    Button difficultyButton(
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 100), 200, 50},
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 100), 200, 50},
            Ocean, "Difficulty: Easy");
    Button scoreLimitButton(
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 170), 200, 50},
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 170), 200, 50},
            Ocean, "Score Limit: " + to_string(scoreLimit));
    Button restartButton(
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 100), 200, 50},
            Rectangle{static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 100), 200, 50},
            Ocean, "Restart");
    Button pauseButton(
            Rectangle{static_cast<float>(screen_width - 150), static_cast<float>(10), 140, 30},
            Rectangle{static_cast<float>(screen_width - 150), static_cast<float>(10), 140, 30},
            Ocean, "P to pause");

    //Core Game Loop
    while (!WindowShouldClose())
    {
        if (!gameStarted)
        {
            UpdateTitleScreen(startButton, difficultyButton, scoreLimitButton);
            BeginDrawing();
            DrawTitleScreen(startButton, difficultyButton, scoreLimitButton);
            EndDrawing();
        }
        else if (gameOver)
        {
            UpdateGameOverScreen(restartButton);
            BeginDrawing();
            DrawGameOverScreen(restartButton);
            EndDrawing();
        }
        else
        {
            BeginDrawing();

            // Updating
            if (!gamePaused) // Only update game logic when not paused
            {
                ball.Update(cpu_score, player_score, scoreLimit, high_score, gameOver);
                player.Update();
                cpu.Update(ball.y);

                // Checking for collisions with slight overlap
                if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                            player.GetCollisionRect()))
                {
                    ball.speed_x *= -1;
                }

                if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                            Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
                {
                    ball.speed_x *= -1;
                }
            }

            // Drawing
            ClearBackground(Royal_Blue);
            DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Ocean);
            DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
            DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
            ball.Draw();
            cpu.Draw();
            player.Draw();
            DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

            pauseButton.Draw();

            EndDrawing();
        }

        // Pause/unpause the game when the P key is pressed
        if (IsKeyPressed(KEY_P) || pauseButton.IsPressed())
        {
            gamePaused = !gamePaused;
        }
    }

    CloseWindow();
    return 0;
}
