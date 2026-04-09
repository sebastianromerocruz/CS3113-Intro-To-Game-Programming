#include "CS3113/ShaderProgram.h"

// Global Constants
constexpr int SCREEN_WIDTH     = 1000,
              SCREEN_HEIGHT    = 600,
              FPS              = 120,
              NUMBER_OF_LEVELS = 2;

constexpr Vector2 ORIGIN = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
            
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

Scene *gCurrentScene = nullptr;
std::vector<Scene*> gLevels = {};

LevelA *gLevelA = nullptr;
LevelB *gLevelB = nullptr;

Effects *gEffects = nullptr;

Camera2D gCamera = { 0 };
ShaderProgram gShader;
Vector2 gLightPosition = { 0.0f, 0.0f };

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

    gLevelA = new LevelA(ORIGIN, "#C0897E");
    gLevelB = new LevelB(ORIGIN, "#011627");

    gLevels.push_back(gLevelA);
    gLevels.push_back(gLevelB);

    switchToScene(gLevels[0]);

    gCamera.offset   = ORIGIN;
    gCamera.rotation = 0.0f;
    gCamera.zoom     = 1.0f;

    gEffects = new Effects(ORIGIN, (float) SCREEN_WIDTH * 1.5f, (float) SCREEN_HEIGHT * 1.5f);

    gEffects->start(SHRINK);
    gEffects->setEffectSpeed(2.0f);

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

        gLightPosition = gCurrentScene->getState().xochitl->getPosition();

        deltaTime -= FIXED_TIMESTEP;
    }
}

void render()
{
    BeginDrawing();
    BeginMode2D(gCamera);
    gShader.begin();

    gShader.setVector2("lightPosition", gLightPosition);
    gCurrentScene->render();

    gShader.end();
    gEffects->render();
    EndMode2D();
    EndDrawing();
}

void shutdown() 
{
    delete gLevelA;
    delete gLevelB;

    for (int i = 0; i < NUMBER_OF_LEVELS; i++) gLevels[i] = nullptr;

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

        if (gCurrentScene->getState().nextSceneID > 0)
        {
            int id = gCurrentScene->getState().nextSceneID;
            switchToScene(gLevels[id]);
        }

        render();
    }

    shutdown();

    return 0;
}