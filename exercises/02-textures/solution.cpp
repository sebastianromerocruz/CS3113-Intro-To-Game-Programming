#include "CS3113/cs3113.h"
#include <map>
#include <array>
#include <string>
#include <math.h>

enum Member { MURDOC, TWO_D, RUSSEL, NOODLE };

// Global Constants
constexpr int   SCREEN_WIDTH  = 1600 / 2,
                SCREEN_HEIGHT = 900 / 2,
                FPS           = 60,
                SIZE          = 200,
                FRAME_LIMIT   = 100;
constexpr float MAX_AMP       = 10.0f;

constexpr char    BG_COLOUR[] = "#000000";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
constexpr Vector2 BASE_SIZE   = { (float) SIZE, (float) SIZE };

const std::map<Member, std::array<bool, 2>> UV_COORDINATES {
    {MURDOC,  {false, false}},
    {TWO_D,   {true,  false}},
    {RUSSEL,  {true,  true} },
    {NOODLE,  {false, true} }
};

// Image owned by Gorillaz @see https://gorillaz.com/
constexpr char ALBUM_COVER_FP[] = "assets/demon_days.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gScaleFactor   = SIZE,
          gAngle         = 0.0f,
          gPulseTime     = 0.0f;
Vector2   gPosition      = ORIGIN;
Vector2   gScale         = BASE_SIZE;
float     gPreviousTicks = 0.0f;
Member    gCurrentMember = NOODLE;
int       gFrameCounter  = 0;

Texture2D gTeardropTexture;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures");

    gTeardropTexture = LoadTexture(ALBUM_COVER_FP);

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    // Heartbeat
    gPulseTime += 1.0f * deltaTime;

    gScale = {
        BASE_SIZE.x + MAX_AMP * cos(gPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gPulseTime)
    };

    // Changing member every 100 frames
    if (gFrameCounter++ % FRAME_LIMIT == 0)
    {
        switch (gCurrentMember)
        {
            case MURDOC: gCurrentMember = TWO_D;  break;
            case TWO_D:  gCurrentMember = NOODLE; break;
            case NOODLE: gCurrentMember = RUSSEL; break;
            case RUSSEL: gCurrentMember = MURDOC; break;
            default:                              break;
        };
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    // Extract the switches for specific member
    std::array<bool, 2> switches = UV_COORDINATES.at(gCurrentMember);

    // UV coordinates of specific member
    Rectangle textureArea = {
        /*
        TOP LEFT CORNER
        ---------------
        If the "switch" is turned on, then we're starting at the texture's
        normal starting points. However, if they are turned off, then we
        are starting from half-way length- and/or width-wise, depending
        on the member.
        */
        switches[0] ? 0.0f : static_cast<float>(gTeardropTexture.width)  / 2.0f,
        switches[1] ? 0.0f : static_cast<float>(gTeardropTexture.height) / 2.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTeardropTexture.width)  / 2.0f,
        static_cast<float>(gTeardropTexture.height) / 2.0f
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        gPosition.x,
        gPosition.y,
        static_cast<float>(gScale.x),
        static_cast<float>(gScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 objectOrigin = {
        static_cast<float>(gScale.x) / 2.0f,
        static_cast<float>(gScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        gTeardropTexture, 
        textureArea, 
        destinationArea, 
        objectOrigin, 
        gAngle, 
        WHITE
    );

    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow();
    UnloadTexture(gTeardropTexture);
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