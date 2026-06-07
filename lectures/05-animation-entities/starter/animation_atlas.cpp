#include "CS3113/animation/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1600 / 2,
              SCREEN_HEIGHT = 900 / 2,
              FPS           = 120,
              SIZE          = 500 / 2,
              SPEED         = 200,

              FRAMES_PER_SECOND = 8;

constexpr float SIZE_RATIO = 48.0f / 64.0f;

constexpr char    BG_COLOUR[] = "#404F59";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
                  BASE_SIZE   = { (float) SIZE * SIZE_RATIO, (float) SIZE },
                  SPRITESHEET_DIMENSIONS = { 8, 6 };

constexpr TextureType TEXTURE_TYPE = ATLAS;

const std::vector<int> DOWN_ANIMATIONS = { 0, 1, 2, 3, 4, 5, 6, 7 };

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

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
Rectangle getUVRectangle(const Texture2D *texture, int index, int rows, int cols);
bool isColliding(const Vector2 *positionA, const Vector2 *scaleA,
    const Vector2 *positionB, const Vector2 *scaleB);

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

bool isColliding(const Vector2 *positionA,  const Vector2 *scaleA,
                 const Vector2 *positionB, const Vector2 *scaleB)
{
    float xDistance = fabs(positionA->x - positionB->x) - ((scaleA->x + scaleB->x) / 2.0f);
    float yDistance = fabs(positionA->y - positionB->y) - ((scaleA->y + scaleB->y) / 2.0f);

    return xDistance < 0.0f && yDistance < 0.0f;
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
            textureArea = getUVRectangle(texture, gAnimationIndex, 6, 8);
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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation (Atlas)");
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

    if      (IsKeyDown(KEY_A)) gMovement.x = -1;
    else if (IsKeyDown(KEY_D)) gMovement.x =  1;
    if      (IsKeyDown(KEY_W)) gMovement.y = -1;
    else if (IsKeyDown(KEY_S)) gMovement.y =  1;

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
            gAnimationIndex %= DOWN_ANIMATIONS.size();
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
