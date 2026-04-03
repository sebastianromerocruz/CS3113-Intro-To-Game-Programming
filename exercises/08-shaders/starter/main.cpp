#include "CS3113/ShaderProgram.h"

// Global Constants
constexpr int SCREEN_WIDTH     = 1000,
              SCREEN_HEIGHT    = 600,
              FPS              = 120,
              NUMBER_OF_LEVELS = 1;

constexpr Vector2 ORIGIN = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
            
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

Scene *gCurrentScene = nullptr;
std::vector<Scene*> gLevels = {};

Camera2D gCamera = { 0 };

Dungeon *gDungeon = nullptr;

Effects *gEffects = nullptr;

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
    gCurrentScene = scene;
    gCurrentScene->initialise();
    gCamera.target = gCurrentScene->getState().hinako->getPosition();
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Effects & Shaders");
    InitAudioDevice();

    gShader.load("shaders/vertex.glsl", "shaders/fragment.glsl");

    gDungeon = new Dungeon(ORIGIN, "#011627");

    gLevels.push_back(gDungeon);

    switchToScene(gLevels[0]);

    gCamera.offset   = ORIGIN;
    gCamera.rotation = 0.0f;
    gCamera.zoom     = 1.0f;

    gEffects = new Effects(ORIGIN, (float) SCREEN_WIDTH * 1.25f, (float) SCREEN_HEIGHT * 1.25f);

    gEffects->start(FADEIN);
    gEffects->setEffectSpeed(0.33f);

    SetTargetFPS(FPS);
}

void processInput() 
{
    gCurrentScene->getState().hinako->resetMovement();

    if      (IsKeyDown(KEY_A)) gCurrentScene->getState().hinako->moveLeft();
    else if (IsKeyDown(KEY_D)) gCurrentScene->getState().hinako->moveRight();

    if (GetLength(gCurrentScene->getState().hinako->getMovement()) > 1.0f) 
        gCurrentScene->getState().hinako->normaliseMovement();

    Animation hinakosCurrAnim = gCurrentScene->getState().hinako->getAnimation();

    if ((IsKeyDown(KEY_S) && hinakosCurrAnim != CHARGING) || IsKeyReleased(KEY_S)) 
        gCurrentScene->getState().hinako->charge();

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

        Vector2 cameraTarget = { gCurrentScene->getState().hinako->getPosition().x, ORIGIN.y };

        if (gCurrentScene->getState().hinako->getPosition().x > gCurrentScene->getState().map->getLeftBoundary()  + (GetScreenWidth() / 2) &&
            gCurrentScene->getState().hinako->getPosition().x < gCurrentScene->getState().map->getRightBoundary() - (GetScreenWidth() / 2))
            panCamera(&gCamera, &cameraTarget);

        gEffects->update(FIXED_TIMESTEP, &cameraTarget);

        gLightPosition = gCurrentScene->getState().hinako->getPosition();

        deltaTime -= FIXED_TIMESTEP;
    }
}

void render()
{
    BeginDrawing();
    BeginMode2D(gCamera);
    gShader.begin();

    gCurrentScene->render();
    gShader.setVector2("lightPosition", gLightPosition);

    gShader.end();
    gEffects->render();
    EndMode2D();
    EndDrawing();
}

void shutdown() 
{
    delete gDungeon;

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