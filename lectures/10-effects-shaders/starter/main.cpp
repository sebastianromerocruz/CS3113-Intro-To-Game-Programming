#include "CS3113/ShaderProgram.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1000,
              SCREEN_HEIGHT = 600,
              FPS           = 120;

constexpr Vector2 ORIGIN = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

Camera2D gCamera = { 0 };

Scene                     *gCurrentScene = nullptr;
std::map<SceneID, Scene *> gLevels       = {};

Effects *gEffects = nullptr;

ShaderProgram gShader;

// Function Declarations
void switchToScene(Scene *scene);
void initialise();
void processInput();
void update();
void render();
void shutdown();

void switchToScene(Scene *scene)
{
    if (gCurrentScene) gCurrentScene->shutdown();
    gCurrentScene = scene;
    gCurrentScene->initialise();
    gCamera.target = gCurrentScene->getState().xochitl->getPosition();
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Effects & Shaders");
    InitAudioDevice();

    gShader.load("shaders/vertex.glsl", "shaders/fragment.glsl");

    gLevels[LEVEL_A] = new LevelA(ORIGIN, "#C0897E");
    gLevels[LEVEL_B] = new LevelB(ORIGIN, "#011627");

    switchToScene(gLevels[LEVEL_A]);

    gCamera.offset   = ORIGIN;
    gCamera.rotation = 0.0f;
    gCamera.zoom     = 1.0f;

    gEffects = new Effects(ORIGIN, (float) SCREEN_WIDTH * 1.5f, (float) SCREEN_HEIGHT * 1.5f);

    // gEffects->start(FADEIN);
    // gEffects->start(FADEOUT);
    // gEffects->start(SHRINK);
    // gEffects->start(GROW);

    SetTargetFPS(FPS);
}

void processInput()
{
    gCurrentScene->getState().xochitl->resetMovement();

    if      (IsKeyDown(KEY_A)) gCurrentScene->getState().xochitl->moveLeft();
    else if (IsKeyDown(KEY_D)) gCurrentScene->getState().xochitl->moveRight();

    if (IsKeyPressed(KEY_W) &&
        gCurrentScene->getState().xochitl->isCollidingBottom())
    {
        gCurrentScene->getState().xochitl->jump();
        PlaySound(gCurrentScene->getState().jumpSound);
    }

    if (GetLength(gCurrentScene->getState().xochitl->getMovement()) > 1.0f)
        gCurrentScene->getState().xochitl->normaliseMovement();

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        gCurrentScene->update(FIXED_TIMESTEP);

        Vector2 cameraTarget = { gCurrentScene->getState().xochitl->getPosition().x, ORIGIN.y };
        panCamera(&gCamera, &cameraTarget);
        gEffects->update(FIXED_TIMESTEP, &cameraTarget);

        deltaTime -= FIXED_TIMESTEP;
    }
}

void render()
{
    BeginDrawing();
    BeginMode2D(gCamera);
    gShader.begin();

    gCurrentScene->render();

    gShader.end();
    gEffects->render();
    EndMode2D();
    EndDrawing();
}

void shutdown()
{
    for (std::pair<const SceneID, Scene *> &entry : gLevels)
        delete entry.second;
    gLevels.clear();

    delete gEffects;
    gEffects = nullptr;

    gShader.unload();

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

        if (gCurrentScene->getState().nextSceneID != NO_SCENE)
        {
            SceneID id = gCurrentScene->getState().nextSceneID;
            switchToScene(gLevels[id]);
        }

        render();
    }

    shutdown();

    return 0;
}
