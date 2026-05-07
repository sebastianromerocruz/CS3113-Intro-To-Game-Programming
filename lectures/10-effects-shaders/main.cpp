/**
* Author: Weixin Wang
* Assignment: Highway Rush
* Date due: 2026-04-24, 2:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "CS3113/ShaderProgram.h"
#include "CS3113/LevelC.h"

constexpr int SCREEN_WIDTH = 1000,
              SCREEN_HEIGHT = 600,
              FPS = 120,
              NUMBER_OF_SCENES = 6;

constexpr Vector2 ORIGIN = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

AppStatus gAppStatus = RUNNING;
float gPreviousTicks = 0.0f,
      gTimeAccumulator = 0.0f;

int gLives = 3;

Scene *gCurrentScene = nullptr;
std::vector<Scene*> gScenes = {};

MenuScreen *gMenuScreen = nullptr;
LevelA *gLevelA = nullptr;
LevelB *gLevelB = nullptr;
LevelC *gLevelC = nullptr;
WinScreen *gWinScreen = nullptr;
LoseScreen *gLoseScreen = nullptr;

Effects *gEffects = nullptr;

Camera2D gCamera = {0};
ShaderProgram gShader;

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

    if (gCurrentScene->isGameplay())
        gCurrentScene->getState().lives = gLives;

    gCamera.target = ORIGIN;
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Highway Rush");
    InitAudioDevice();

    gShader.load("shaders/vertex.glsl", "shaders/fragment.glsl");

    gMenuScreen = new MenuScreen(ORIGIN, "#1a1a2e");
    gLevelA     = new LevelA(ORIGIN, "#2d5a27");
    gLevelB     = new LevelB(ORIGIN, "#c2a14d");
    gLevelC     = new LevelC(ORIGIN, "#d0dce5");
    gWinScreen  = new WinScreen(ORIGIN, "#0f3d0f");
    gLoseScreen = new LoseScreen(ORIGIN, "#3d0f0f");

    gScenes.push_back(gMenuScreen); 
    gScenes.push_back(gLevelA);      
    gScenes.push_back(gLevelB);     
    gScenes.push_back(gLevelC);      
    gScenes.push_back(gWinScreen);   
    gScenes.push_back(gLoseScreen);  

    switchToScene(gScenes[0]);

    gCamera.offset   = ORIGIN;
    gCamera.rotation = 0.0f;
    gCamera.zoom     = 1.0f;

    gEffects = new Effects(ORIGIN, (float) SCREEN_WIDTH * 1.5f, (float) SCREEN_HEIGHT * 1.5f);
    gEffects->start(NONE);
    gEffects->setEffectSpeed(2.0f);

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
    if (IsKeyPressed(KEY_ONE))   { gLives = 3; switchToScene(gScenes[1]); }
    if (IsKeyPressed(KEY_TWO))   { gLives = 3; switchToScene(gScenes[2]); }
    if (IsKeyPressed(KEY_THREE)) { gLives = 3; switchToScene(gScenes[3]); }
    if (IsKeyPressed(KEY_ZERO))  { gLives = 3; switchToScene(gScenes[0]); }
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

        Vector2 cameraTarget = ORIGIN;
        gEffects->update(FIXED_TIMESTEP, &cameraTarget);

        deltaTime -= FIXED_TIMESTEP;
    }

    if (gCurrentScene->isGameplay())
        gLives = gCurrentScene->getState().lives;
}

void render()
{
    BeginDrawing();
    BeginMode2D(gCamera);

    float blizzard = 0.0f;
    if (gCurrentScene->isGameplay())
        blizzard = gCurrentScene->getState().blizzardIntensity;

    gShader.setFloat("blizzardIntensity", blizzard);
    gShader.setFloat("time", (float)GetTime());

    if (blizzard > 0.0f)
        gShader.begin();

    gCurrentScene->render();

    if (blizzard > 0.0f)
        gShader.end();

    gEffects->render();
    EndMode2D();
    EndDrawing();
}

void shutdown() 
{
    delete gMenuScreen;
    delete gLevelA;
    delete gLevelB;
    delete gLevelC;
    delete gWinScreen;
    delete gLoseScreen;

    for (int i = 0; i < NUMBER_OF_SCENES; i++) gScenes[i] = nullptr;

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

        int nextID = gCurrentScene->getState().nextSceneID;
        if (nextID >= 0)
        {
            if (nextID == 0) gLives = 3;

            gEffects->start(FADEIN);
            gEffects->setEffectSpeed(3.0f);
            switchToScene(gScenes[nextID]);
        }

        render();
    }

    shutdown();

    return 0;
}
