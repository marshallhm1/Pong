#include "Button.h"

Button::Button(Rectangle container, Rectangle rect, Color color, const std::string& text)
        : container(container), rect(rect), color(color), text(text)
{
}

bool Button::IsPressed()
{
    Vector2 mousePosition = GetMousePosition();
    return CheckCollisionPointRec(mousePosition, container) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Button::Draw()
{
    DrawRectangle(static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.width), static_cast<int>(rect.height), color);
    DrawText(text.c_str(), static_cast<int>(rect.x + rect.width / 2 - MeasureText(text.c_str(), 20) / 2),
             static_cast<int>(rect.y + rect.height / 2 - 10), 20, WHITE);
}
