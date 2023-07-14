#ifndef BALL_H
#define BALL_H

#include <raylib.h>

class Ball
{
public:
    float x, y;
    float radius;
    float speed_x, speed_y;

    void Draw();
    void Update(int& cpu_score, int& player_score, int scoreLimit, int& high_score, bool& gameOver);
};

#endif
