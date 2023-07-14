#include "Ball.h"
#include <iostream>

void Ball::Draw()
{
    DrawCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(radius), YELLOW);
}

void Ball::Update(int& cpu_score, int& player_score, int scoreLimit, int& high_score, bool& gameOver)
{
    x += speed_x;
    y += speed_y;

    // Ball collision with walls
    if (y >= GetScreenHeight() - radius || y <= radius)
    {
        speed_y *= -1;
    }

    // Ball collision with paddles
    if (x >= GetScreenWidth() - radius || x <= radius)
    {
        if (x >= GetScreenWidth() - radius)
        {
            cpu_score++;
        }
        else
        {
            player_score++;
        }

        if (player_score > high_score)  // Update high score
        {
            high_score = player_score;
        }

        if (player_score >= scoreLimit || cpu_score >= scoreLimit)
        {
            gameOver = true;
        }

        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        speed_x *= -1;
        speed_y *= -1;
    }
}
