#include "raylib.h"
#include <cstdio>

// Enums
enum AppStatus { TERMINATED, RUNNING };
enum Direction { LEFT, RIGHT };       // turning left or right?

// Global Constants
constexpr int SCREEN_WIDTH  = 1200,
              SCREEN_HEIGHT = 675,
              FPS           = 60;

constexpr float LIMIT_ANGLE = 20.0f;  // when turning directions will flip

// Global Variables
AppStatus gAppStatus = RUNNING;
Direction gDirection = RIGHT;         // start by rotating right
float gScaleFactor   = 100.0f,
      gAngle         = 0.0f;
Vector2 gPosition    = { 0.0f, 0.0f };

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// You can ignore this function, it's just to get nice colours :)
Color ColorFromHex(const char *hex)
{
    // Skip leading '#', if present
    if (hex[0] == '#') hex++;

    // Default alpha = 255 (opaque)
    unsigned int r = 0, 
                 g = 0, 
                 b = 0, 
                 a = 255;

    // 6‑digit form: RRGGBB
    if (sscanf(hex, "%02x%02x%02x", &r, &g, &b) == 3) {
        return Color{ static_cast<unsigned char>(r),
                      static_cast<unsigned char>(g),
                      static_cast<unsigned char>(b),
                      static_cast<unsigned char>(a) };
    }

    // 8‑digit form: RRGGBBAA
    if (sscanf(hex, "%02x%02x%02x%02x", &r, &g, &b, &a) == 4) {
        return Color{ static_cast<unsigned char>(r),
                      static_cast<unsigned char>(g),
                      static_cast<unsigned char>(b),
                      static_cast<unsigned char>(a) };
    }

    // Fallback – return white so you notice something went wrong
    return RAYWHITE;
}

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Transformations");

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    gScaleFactor *= 1.0025f;

    if (gPosition.x < SCREEN_WIDTH)  gPosition.x += 1.0f;
    if (gPosition.y < SCREEN_HEIGHT) gPosition.y += 0.5f;

    // Increase angle by 1.0f times either 1
    // if we're turning right or -1 if we're
    // turning left
    gAngle += (gDirection == RIGHT) ? 1.0f : -1.0f;

    // Once we reach the limit angle, switch direction
    if      (gAngle >  LIMIT_ANGLE) gDirection = LEFT;
    else if (gAngle < -LIMIT_ANGLE) gDirection = RIGHT;
}

void render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawPoly(
        gPosition,
        3, 
        gScaleFactor, 
        gAngle, 
        ColorFromHex("#F88379")
    );

    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow();
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}