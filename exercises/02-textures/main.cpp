#include "CS3113/cs3113.h"
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

// Image owned by Gorillaz @see https://gorillaz.com/
constexpr char ALBUM_COVER_FP[] = "assets/demon_days.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gScaleFactor   = SIZE,
          gAngle         = 0.0f,
          gPulseTime     = 0.0f;
Vector2   gPosition      = ORIGIN;
Vector2   gScale         = BASE_SIZE;

Texture2D gAlbumTexture;

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

    gAlbumTexture = LoadTexture(ALBUM_COVER_FP);

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    /**
     * @todo Calculate delta time
     */


    /**
     * @todo Apply delta time to the time-dependent logic
     */
    gPulseTime += 1.0f;

    gScale = {
        BASE_SIZE.x + MAX_AMP * cos(gPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gPulseTime)
    };

    /**
     * @todo Switch member every 100 fames
     */
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    /**
     * @todo Design your UV coordinates (i.e. textureArea) so that only one
     * member is being rendered onto the screen.
     */
    Rectangle textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gAlbumTexture.width),
        static_cast<float>(gAlbumTexture.height)
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
        gAlbumTexture, 
        textureArea, 
        destinationArea, 
        objectOrigin, 
        gAngle, 
        WHITE
    );

    EndDrawing();
}

void shutdown() { CloseWindow(); }

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