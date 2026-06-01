#include "CS3113/entities/Entity.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1600 / 2,
              SCREEN_HEIGHT = 900 / 2,
              FPS           = 120,
              SIZE          = 500 / 2,
              SPEED         = 200,

              FRAMES_PER_SECOND = 14;

constexpr float SIZE_RATIO = 48.0f / 64.0f;

constexpr char    BG_COLOUR[] = "#404F59";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
                  BASE_SIZE   = { (float) SIZE * SIZE_RATIO, (float) SIZE },
                  SPRITESHEET_DIMENSIONS = { 8, 6 };

constexpr TextureType TEXTURE_TYPE = ATLAS;

const std::map<Direction, std::vector<int>> ANIMATION_ATLAS = {
    {DOWN,  {  0,  1,  2,  3,  4,  5,  6,  7 }},
    {LEFT,  {  8,  9, 10, 11, 12, 13, 14, 15 }},
    {UP,    { 24, 25, 26, 27, 28, 29, 30, 31 }},
    {RIGHT, { 40, 41, 42, 43, 44, 45, 46, 47 }},
};

// Assets from @see https://sscary.itch.io/the-adventurer-female
constexpr char PROTAG_FILEPATH[] = "assets/game/walk.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gAngle         = 0.0f,
          gPreviousTicks = 0.0f,

          gAnimationTime = 0.0f;

Vector2 gPosition  = ORIGIN,
        gMovement  = { 0.0f, 0.0f },
        gScale     = BASE_SIZE;

Texture2D gTexture;

Music gBGM;

int gAnimationIndex = 0;

Direction        gWalkingDirection = DOWN;
std::vector<int> gAnimationIndices = ANIMATION_ATLAS.at(gWalkingDirection);

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
Rectangle getUVRectangle(const Texture2D *texture, int index, int rows, int cols);

Rectangle getUVRectangle(const Texture2D *texture, int index, int rows, int cols)
{
    float uCoord = (float) (index % cols) / (float) cols;
    uCoord *= texture->width;

    float vCoord = (float) (index / cols) / (float) rows;
    vCoord *= texture->height;

    float sliceWidth  = texture->width  / (float) cols;
    float sliceHeight = texture->height / (float) rows;

    return {
        uCoord,     // top-left x-coord
        vCoord,     // top-left y-coord
        sliceWidth, // width of slice
        sliceHeight // height of slice
    };
}

void renderObject(const Texture2D *texture, const Vector2 *position,
                  const Vector2 *scale, TextureType textureType)
{
    Rectangle textureArea;

    switch (textureType)
    {
        case SINGLE:
            // Whole texture (UV coordinates)
            textureArea = {
                // top-left corner
                0.0f, 0.0f,

                // bottom-right corner (of texture)
                static_cast<float>(texture->width),
                static_cast<float>(texture->height)
            };
            break;
        case ATLAS:
            textureArea = getUVRectangle(
                texture,
                gAnimationIndices[gAnimationIndex],
                6, 8
            );
            break;
        default: break;
    }

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        position->x,
        position->y,
        static_cast<float>(scale->x),
        static_cast<float>(scale->y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        static_cast<float>(scale->x) / 2.0f,
        static_cast<float>(scale->y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        *texture,
        textureArea, destinationArea, originOffset,
        gAngle, WHITE
    );
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation / Entities");
    InitAudioDevice();

    gBGM = LoadMusicStream("assets/game/04 - Silent Forest.wav");
    SetMusicVolume(gBGM, 0.33f);
    PlayMusicStream(gBGM);

    gTexture = LoadTexture(PROTAG_FILEPATH);

    SetTargetFPS(FPS);
}

void processInput()
{
    gMovement = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_A))
    {
        gMovement.x = -1;
        gWalkingDirection = LEFT;
    }
    else if (IsKeyDown(KEY_D))
    {
        gMovement.x =  1;
        gWalkingDirection = RIGHT;
    }
    if (IsKeyDown(KEY_W))
    {
        gMovement.y = -1;
        gWalkingDirection = UP;
    }
    else if (IsKeyDown(KEY_S))
    {
        gMovement.y =  1;
        gWalkingDirection = DOWN;
    }

    // to avoid faster diagonal speed
    if (GetLength(&gMovement) > 1.0f) Normalise(&gMovement);

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    gAnimationIndices = ANIMATION_ATLAS.at(gWalkingDirection);

    gPosition = {
        gPosition.x + SPEED * gMovement.x * deltaTime,
        gPosition.y + SPEED * gMovement.y * deltaTime
    };

    if (GetLength(&gMovement) != 0)
    {
        gAnimationTime += deltaTime;
        float secondsPerFrame = 1.0f / FRAMES_PER_SECOND;

        if (gAnimationTime >= secondsPerFrame)
        {
            gAnimationTime = 0.0f;

            gAnimationIndex++;
            gAnimationIndex %= gAnimationIndices.size();
        }
    }

    UpdateMusicStream(gBGM);
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    renderObject(&gTexture, &gPosition, &gScale, TEXTURE_TYPE);

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gTexture);
    UnloadMusicStream(gBGM);
    CloseAudioDevice();
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
