#include "Paddle.h"

void Paddle::LimitMovement()
{
    if (y <= 0)
    {
        y = 0;
    }
    if (y + height >= GetScreenHeight())
    {
        y = GetScreenHeight() - height;
    }
}

void Paddle::Draw()
{
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), WHITE);
}

void Paddle::Update()
{
    if (IsKeyDown(KEY_UP))
    {
        y -= speed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        y += speed;
    }
    LimitMovement();
}

Rectangle Paddle::GetCollisionRect()
{
    // Introduce a small overlap to avoid ball getting stuck inside the paddle
    const float overlap = 2.0f;
    return {x - overlap, y - overlap, width + overlap * 2, height + overlap * 2};
}

void CpuPaddle::Update(int ball_y)
{
    if (y + height / 2 > ball_y)
    {
        y -= speed;
    }
    if (y + height / 2 <= ball_y)
    {
        y += speed;
    }
    LimitMovement();
}
