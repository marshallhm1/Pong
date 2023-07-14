#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <string>

class Button
{
public:
    Rectangle container;
    Rectangle rect;
    Color color;
    std::string text;

    Button(Rectangle container, Rectangle rect, Color color, const std::string& text);

    bool IsPressed();
    void Draw();
};

#endif
