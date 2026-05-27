#include "CS3113/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1600 / 2,
              SCREEN_HEIGHT = 900 / 2,
              FPS           = 60,
              SIZE          = 500 / 2,
              SPEED         = 200;

constexpr char    BG_COLOUR[]    = "#F8F1C8";
constexpr Vector2 ORIGIN         = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
                  BASE_SIZE      = { static_cast<float>(SIZE), static_cast<float>(SIZE) },
                  INIT_POS       = { ORIGIN.x - 200.0f, ORIGIN.y },
                  RUPEE_INIT_POS = { ORIGIN.x + 250.0f, ORIGIN.y };

// Images owned by Nintendo — please don't sue me.
constexpr char LINK_FP[]  = "assets/game/awakening-link.png";
constexpr char RUPEE_FP[] = "assets/game/awakening-rupee.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gAngle         = 0.0f,
          gPreviousTicks = 0.0f;

Vector2 gLinkPosition  = INIT_POS,
        gLinkMovement  = { 0.0f, 0.0f },
        gLinkScale     = BASE_SIZE,

        gRupeePosition = RUPEE_INIT_POS,
        gRupeeMovement = { 0.0f, 0.0f },
        gRupeeScale    = { BASE_SIZE.x / 2.0f , BASE_SIZE.y / 2.0f * 1.6f},

        gMousePosition = GetMousePosition();

Texture2D gLinkTexture;
Texture2D gRupeeTexture;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
bool isColliding(const Vector2 *positionA, const Vector2 *scaleA, const Vector2 *positionB, const Vector2 *scaleB);

// Function Definitions

bool isColliding(const Vector2 *positionA,  const Vector2 *scaleA,
                 const Vector2 *positionB, const Vector2 *scaleB)
{
    // TODO: implement AABB collision detection

    return false;
}

void renderObject(const Texture2D *texture, const Vector2 *position,
                  const Vector2 *scale)
{
    Rectangle textureArea = {
        0.0f, 0.0f,
        static_cast<float>(texture->width),
        static_cast<float>(texture->height)
    };

    Rectangle destinationArea = {
        position->x,
        position->y,
        static_cast<float>(scale->x),
        static_cast<float>(scale->y)
    };

    Vector2 originOffset = {
        static_cast<float>(scale->x) / 2.0f,
        static_cast<float>(scale->y) / 2.0f
    };

    DrawTexturePro(
        *texture,
        textureArea, destinationArea, originOffset,
        gAngle, WHITE
    );
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "User Input / Collision Detection");

    gLinkTexture  = LoadTexture(LINK_FP);
    gRupeeTexture = LoadTexture(RUPEE_FP);

    SetTargetFPS(FPS);
}

void processInput()
{
    gLinkMovement = { 0.0f, 0.0f };

    // TODO: handle WASD keyboard input

    // TODO: handle left mouse button input

    // TODO: normalise diagonal movement

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    float ticks    = static_cast<float>(GetTime());
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    gMousePosition = GetMousePosition();

    // TODO: apply movement to gLinkPosition using deltaTime

    // TODO: check for collision between Link and the rupee
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    renderObject(&gLinkTexture,  &gLinkPosition,  &gLinkScale);
    renderObject(&gRupeeTexture, &gRupeePosition, &gRupeeScale);

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gLinkTexture);
    UnloadTexture(gRupeeTexture);
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
