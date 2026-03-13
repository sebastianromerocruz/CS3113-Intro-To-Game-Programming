#include "CS3113/Entity.h"

struct GameState
{
    Entity *xochitl;
    Map *map;

    Music bgm;
    Sound jumpSound;
};

// Global Constants
constexpr int SCREEN_WIDTH  = 1000,
              SCREEN_HEIGHT = 600,
              FPS           = 120;

constexpr char    BG_COLOUR[]      = "#C0897E";
constexpr Vector2 ORIGIN           = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
                  ATLAS_DIMENSIONS = { 6, 8 };

constexpr int   NUMBER_OF_TILES         = 20,
                NUMBER_OF_BLOCKS        = 3;
constexpr float TILE_DIMENSION          = 75.0f,
                // in m/ms², since delta time is in ms
                ACCELERATION_OF_GRAVITY = 981.0f,
                FIXED_TIMESTEP          = 1.0f / 60.0f,
                END_GAME_THRESHOLD      = 800.0f;

constexpr int LEVEL_WIDTH  = 14,
              LEVEL_HEIGHT = 8;
constexpr unsigned int LEVEL_DATA[] = {
   4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
   4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
   4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
   4, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 4,
   4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 4,
   4, 2, 2, 2, 0, 0, 0, 2, 2, 2, 3, 3, 3, 4,
   4, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 4,
   4, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 4
};

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;
Camera2D gCamera       = { 0 };

GameState gState;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
void panCamera(Camera2D *camera, const Vector2 *targetPosition);

/**
 * The function `panCamera` smoothly adjusts the camera's target position towards a specified target
 * position.
 * 
 * @param camera The `camera` parameter is a pointer to a `Camera2D` struct, which likely contains
 * information about a 2D camera such as its position, target, zoom level, and other properties.
 * @param targetPosition The `targetPosition` parameter is a pointer to a `Vector2` structure that
 * represents the desired position where the camera should be focused or centered on.
 */
void panCamera(Camera2D *camera, const Vector2 *targetPosition)
{
    Vector2 positionDifference = Vector2Subtract(
        *targetPosition, 
        camera->target
    );

    camera->target = Vector2Add(
        camera->target, 
        Vector2Scale(positionDifference, 0.1f)
    ); // 0.1 = smoothing factor
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maps");
    InitAudioDevice();

    gState.bgm = LoadMusicStream("assets/game/04 - Silent Forest.wav");
    SetMusicVolume(gState.bgm, 0.33f);
    // PlayMusicStream(gState.bgm);

    gState.jumpSound = LoadSound("assets/game/Dirt Jump.wav");

    /*
        ----------- MAP -----------
    */
    gState.map = new Map(
        LEVEL_WIDTH, LEVEL_HEIGHT,   // map grid cols & rows
        (unsigned int *) LEVEL_DATA, // grid data
        "assets/game/tileset.png",   // texture filepath
        TILE_DIMENSION,              // tile size
        4, 1,                        // texture cols & rows
        ORIGIN                       // in-game origin
    );

    /*
        ----------- PROTAGONIST -----------
    */
    std::map<Direction, std::vector<int>> xochitlAnimationAtlas = {
        {DOWN,  {  0,  1,  2,  3,  4,  5,  6,  7 }},
        {LEFT,  {  8,  9, 10, 11, 12, 13, 14, 15 }},
        {UP,    { 24, 25, 26, 27, 28, 29, 30, 31 }},
        {RIGHT, { 40, 41, 42, 43, 44, 45, 46, 47 }},
    };

    float sizeRatio  = 48.0f / 64.0f;

    // Assets from @see https://sscary.itch.io/the-adventurer-female
    gState.xochitl = new Entity(
        {ORIGIN.x - 300.0f, ORIGIN.y - 200.0f}, // position
        {250.0f * sizeRatio, 250.0f},           // scale
        "assets/game/walk.png",                 // texture file address
        ATLAS,                                  // single image or atlas?
        ATLAS_DIMENSIONS,                       // atlas dimensions
        xochitlAnimationAtlas,                  // actual atlas
        PLAYER                                  // entity type
    );

    gState.xochitl->setJumpingPower(550.0f);
    gState.xochitl->setColliderDimensions({
        gState.xochitl->getScale().x / 3.5f,
        gState.xochitl->getScale().y / 3.0f
    });
    gState.xochitl->setAcceleration({0.0f, ACCELERATION_OF_GRAVITY});

    /*
        ----------- CAMERA -----------
    */
    gCamera.target   = gState.xochitl->getPosition(); // camera follows player
    gCamera.offset   = ORIGIN;                        // camera offset to center of screen
    gCamera.rotation = 0.0f;                          // no rotation
    gCamera.zoom     = 1.0f;                          // default zoom

    SetTargetFPS(FPS);
}

void processInput() 
{
    gState.xochitl->resetMovement();

    if      (IsKeyDown(KEY_A)) gState.xochitl->moveLeft();
    else if (IsKeyDown(KEY_D)) gState.xochitl->moveRight();

    if (IsKeyPressed(KEY_W) && gState.xochitl->isCollidingBottom())
    {
        gState.xochitl->jump();
        PlaySound(gState.jumpSound);
    }

    if (GetLength(gState.xochitl->getMovement()) > 1.0f) 
        gState.xochitl->normaliseMovement();

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    // Fixed timestep
    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        UpdateMusicStream(gState.bgm);

        gState.xochitl->update(
            FIXED_TIMESTEP, // delta time / fixed timestep
            nullptr,        // player
            gState.map,     // map
            nullptr,        // collidable entities
            0               // col. entity count
        );

        deltaTime -= FIXED_TIMESTEP;

        Vector2 currentPlayerPosition = { gState.xochitl->getPosition().x, ORIGIN.y };

        panCamera(&gCamera, &currentPlayerPosition);

        if (gState.xochitl->getPosition().y > 800.0f) gAppStatus = TERMINATED;
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    BeginMode2D(gCamera);

    gState.xochitl->render();
    gState.map->render();

    EndMode2D();

    EndDrawing();
}

void shutdown() 
{
    delete gState.xochitl;
    delete gState.map;

    UnloadMusicStream(gState.bgm);
    UnloadSound(gState.jumpSound);

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