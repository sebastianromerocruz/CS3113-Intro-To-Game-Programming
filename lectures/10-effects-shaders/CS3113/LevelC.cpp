#include "LevelC.h"

static constexpr float ROAD_LEFT  = 300.0f;
static constexpr float ROAD_RIGHT = 700.0f;
static constexpr float ROAD_WIDTH = 400.0f;
static constexpr float LANE_1     = 367.0f;
static constexpr float LANE_2     = 500.0f;
static constexpr float LANE_3     = 633.0f;
static constexpr float PLAYER_Y   = 450.0f;
static constexpr float ROAD_MIN_X = 320.0f;
static constexpr float ROAD_MAX_X = 680.0f;

static float sLanePositions[3] = { LANE_1, LANE_2, LANE_3 };

static std::map<Direction, std::vector<int>> sCarAtlas = {
    {UP, {6}}, {DOWN, {2}}, {LEFT, {8}}, {RIGHT, {0}},
};

static bool checkOverlap(Entity *a, Entity *b)
{
    float dx = fabs(a->getPosition().x - b->getPosition().x);
    float dy = fabs(a->getPosition().y - b->getPosition().y);
    float ox = (a->getColliderDimensions().x + b->getColliderDimensions().x) / 2.0f;
    float oy = (a->getColliderDimensions().y + b->getColliderDimensions().y) / 2.0f;
    return (dx < ox && dy < oy);
}

static void setupEnemy(Entity *e, const char *texture, AIType aiType,
                       int speed, Direction dir, Vector2 scale, Vector2 collider)
{
    e->setTexture(texture);
    e->setTextureType(ATLAS);
    e->setSpriteSheetDimensions({3, 3});
    e->setAnimationAtlas(sCarAtlas);
    e->setEntityType(NPC);
    e->setAIType(aiType);
    e->setSpeed(speed);
    e->setDirection(dir);
    e->setScale(scale);
    e->setColliderDimensions(collider);
    e->setPosition({-500.0f, -500.0f});
    e->deactivate();
}

LevelC::LevelC()                                      : Scene { {0.0f}, nullptr   } {}
LevelC::LevelC(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}
LevelC::~LevelC() { shutdown(); }

void LevelC::initialise()
{
    mGameState.nextSceneID       = -1;
    mGameState.lives             = 3;
    mGameState.distanceTraveled  = 0.0f;
    mGameState.targetDistance    = TARGET_DISTANCE;
    mGameState.scrollSpeed       = BASE_SCROLL;
    mGameState.roadScrollOffset  = 0.0f;
    mGameState.invincibilityTimer = 0.0f;
    mGameState.spawnTimer        = 1.0f;
    mGameState.pickupSpawnTimer  = 8.0f;
    mGameState.blizzardIntensity = 0.0f;
    mGameState.copCaught         = false;
    mGameState.map               = nullptr;

    mGameState.bgTexture = LoadTexture("assets/game/snow.png");
    mGameState.roadTexture = LoadTexture("assets/game/road_vertical.png");

    mGameState.bgm = LoadMusicStream("assets/game/snow_music.mp3");
    SetMusicVolume(mGameState.bgm, 0.5f);
    PlayMusicStream(mGameState.bgm);

    mGameState.collisionSound = LoadSound("assets/game/crash.ogg");
    mGameState.pickupSound    = LoadSound("assets/game/pickup_sfx.wav");
    mGameState.sirenSound     = LoadSound("assets/game/siren.wav");

    mGameState.player = new Entity(
        {mOrigin.x, PLAYER_Y}, {60.0f, 60.0f},
        "assets/game/player.png", ATLAS, {3, 3}, sCarAtlas, PLAYER
    );
    mGameState.player->setSpeed(350);
    mGameState.player->setColliderDimensions({40.0f, 50.0f});
    mGameState.player->setDirection(UP);
    mGameState.player->setAngle(0.0f);

    mGameState.enemyCount = MAX_ENEMIES;
    mGameState.enemies    = new Entity[MAX_ENEMIES];

    for (int i = 0; i < 4; i++)
        setupEnemy(&mGameState.enemies[i], "assets/game/truck.png",
                   TRAFFIC, 260, UP, {80.0f, 80.0f}, {55.0f, 65.0f});

    for (int i = 4; i < 8; i++)
        setupEnemy(&mGameState.enemies[i], "assets/game/racer.png",
                   ONCOMING, 680, DOWN, {60.0f, 60.0f}, {40.0f, 50.0f});

    for (int i = 8; i < 12; i++)
        setupEnemy(&mGameState.enemies[i], "assets/game/taxi.png",
                   TRAFFIC, 280, UP, {60.0f, 60.0f}, {40.0f, 50.0f});

    for (int i = 12; i < MAX_ENEMIES; i++)
        setupEnemy(&mGameState.enemies[i], "assets/game/police.png",
                   COP, 300, UP, {60.0f, 60.0f}, {40.0f, 50.0f});

    mGameState.pickupCount = MAX_PICKUPS;
    mGameState.pickups     = new Entity[MAX_PICKUPS];

    for (int i = 0; i < MAX_PICKUPS; i++)
    {
        mGameState.pickups[i].setTexture("assets/game/heart.png");
        mGameState.pickups[i].setTextureType(SINGLE);
        mGameState.pickups[i].setEntityType(PICKUP);
        mGameState.pickups[i].setScale({30.0f, 30.0f});
        mGameState.pickups[i].setColliderDimensions({25.0f, 25.0f});
        mGameState.pickups[i].setPosition({-500.0f, -500.0f});
        mGameState.pickups[i].deactivate();
    }
}

void LevelC::update(float deltaTime)
{
    if (mGameState.lives <= 0) return;

    UpdateMusicStream(mGameState.bgm);

    mGameState.player->resetMovement();
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  mGameState.player->moveLeft();
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) mGameState.player->moveRight();

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        mGameState.scrollSpeed = BASE_SCROLL * 1.5f;
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        mGameState.scrollSpeed = BASE_SCROLL * 0.5f;
    else
        mGameState.scrollSpeed = BASE_SCROLL;

    float px = mGameState.player->getPosition().x;
    px += mGameState.player->getMovement().x * mGameState.player->getSpeed() * deltaTime;
    if (px < ROAD_MIN_X) px = ROAD_MIN_X;
    if (px > ROAD_MAX_X) px = ROAD_MAX_X;
    mGameState.player->setPosition({px, PLAYER_Y});

    mGameState.roadScrollOffset += mGameState.scrollSpeed * deltaTime;
    mGameState.distanceTraveled += mGameState.scrollSpeed * deltaTime * 0.05f;

    float progress = mGameState.distanceTraveled / mGameState.targetDistance;
    mGameState.blizzardIntensity = fminf(progress * 1.2f, 0.75f);

    if (mGameState.invincibilityTimer > 0.0f)
        mGameState.invincibilityTimer -= deltaTime;

    mGameState.spawnTimer -= deltaTime;
    if (mGameState.spawnTimer <= 0.0f)
    {
        int spawned = 0;
        for (int i = 0; i < 12; i++)
        {
            if (!mGameState.enemies[i].isActive())
            {
                int lane = GetRandomValue(0, 2);

                if (mGameState.enemies[i].getAIType() == ONCOMING)
                    mGameState.enemies[i].setPosition({sLanePositions[lane], 680.0f});
                else
                    mGameState.enemies[i].setPosition({sLanePositions[lane], -80.0f});

                mGameState.enemies[i].activate();
                spawned++;
                if (spawned >= 3) break;
            }
        }
        mGameState.spawnTimer = GetRandomValue(8, 15) / 10.0f;
    }

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!mGameState.enemies[i].isActive()) continue;
        mGameState.enemies[i].update(deltaTime, mGameState.player, nullptr, nullptr, 0);
        if (mGameState.enemies[i].getPosition().y > 750.0f ||
            mGameState.enemies[i].getPosition().y < -250.0f)
            mGameState.enemies[i].deactivate();
    }

    mGameState.pickupSpawnTimer -= deltaTime;
    if (mGameState.pickupSpawnTimer <= 0.0f)
    {
        for (int i = 0; i < MAX_PICKUPS; i++)
        {
            if (!mGameState.pickups[i].isActive())
            {
                int lane = GetRandomValue(0, 2);
                mGameState.pickups[i].setPosition({sLanePositions[lane], -40.0f});
                mGameState.pickups[i].activate();
                break;
            }
        }
        mGameState.pickupSpawnTimer = GetRandomValue(60, 120) / 10.0f;
    }

    for (int i = 0; i < MAX_PICKUPS; i++)
    {
        if (!mGameState.pickups[i].isActive()) continue;
        float py = mGameState.pickups[i].getPosition().y + 200.0f * deltaTime;
        mGameState.pickups[i].setPosition({mGameState.pickups[i].getPosition().x, py});
        if (py > 700.0f) mGameState.pickups[i].deactivate();
    }

    if (mGameState.invincibilityTimer <= 0.0f)
    {
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (!mGameState.enemies[i].isActive()) continue;
            if (checkOverlap(mGameState.player, &mGameState.enemies[i]))
            {
                mGameState.lives--;
                mGameState.invincibilityTimer = 2.0f;
                PlaySound(mGameState.collisionSound);

                if (mGameState.enemies[i].getAIType() == COP)
                    mGameState.copCaught = true;

                mGameState.enemies[i].deactivate();

                for (int p = 12; p < MAX_ENEMIES; p++)
                {
                    if (!mGameState.enemies[p].isActive())
                    {
                        int lane = GetRandomValue(0, 2);
                        mGameState.enemies[p].setPosition({sLanePositions[lane], -100.0f});
                        mGameState.enemies[p].activate();
                        PlaySound(mGameState.sirenSound);
                        break;
                    }
                }

                if (mGameState.lives <= 0) { mGameState.nextSceneID = 5; return; }
                break;
            }
        }
    }

    for (int i = 0; i < MAX_PICKUPS; i++)
    {
        if (!mGameState.pickups[i].isActive()) continue;
        if (checkOverlap(mGameState.player, &mGameState.pickups[i]))
        {
            if (mGameState.lives < 3) mGameState.lives++;
            mGameState.pickups[i].deactivate();
            PlaySound(mGameState.pickupSound);
        }
    }

    if (mGameState.distanceTraveled >= mGameState.targetDistance)
        mGameState.nextSceneID = 4; 
}

void LevelC::render()
{
    ClearBackground(ColorFromHex("#d0dce5"));
    float bgH = (float)mGameState.bgTexture.height;
    float bgW = (float)mGameState.bgTexture.width;
    float bgScrollY = fmod(mGameState.roadScrollOffset * 0.3f, bgH);

    for (float y = -bgH + bgScrollY; y < 620.0f; y += bgH)
    {
        DrawTexturePro(mGameState.bgTexture,
            {0, 0, bgW, bgH},
            {0, y, ROAD_LEFT, bgH},
            {0, 0}, 0.0f, WHITE);

        DrawTexturePro(mGameState.bgTexture,
            {0, 0, bgW, bgH},
            {ROAD_RIGHT, y, 300.0f, bgH},
            {0, 0}, 0.0f, WHITE);
    }

    float roadW = (float)mGameState.roadTexture.width;
    float roadH = (float)mGameState.roadTexture.height;
    float scaledH = roadH * (ROAD_WIDTH / roadW);
    float scrollY = fmod(mGameState.roadScrollOffset, scaledH);

    for (float y = -scaledH + scrollY; y < 620.0f; y += scaledH)
    {
        DrawTexturePro(mGameState.roadTexture,
            {0, 0, roadW, roadH},
            {ROAD_LEFT, y, ROAD_WIDTH, scaledH},
            {0, 0}, 0.0f, WHITE);
    }

    for (int i = 0; i < MAX_ENEMIES; i++)
        mGameState.enemies[i].render();

    for (int i = 0; i < MAX_PICKUPS; i++)
        mGameState.pickups[i].render();

    if (mGameState.invincibilityTimer > 0.0f)
    {
        if ((int)(mGameState.invincibilityTimer * 8) % 2 == 0)
            mGameState.player->render();
    }
    else
        mGameState.player->render();

    DrawRectangle(0, 0, 1000, 40, Fade(BLACK, 0.6f));
    for (int i = 0; i < mGameState.lives; i++)
        DrawRectangle(20 + i * 35, 8, 24, 24, RED);

    const char *lvl = "BLIZZARD MOUNTAIN";
    DrawText(lvl, 200, 10, 22, RAYWHITE);

    char distBuf[64];
    snprintf(distBuf, sizeof(distBuf), "%.0f m / %.0f m",
             mGameState.distanceTraveled, mGameState.targetDistance);
    int dw = MeasureText(distBuf, 22);
    DrawText(distBuf, 980 - dw, 10, 22, RAYWHITE);
}

void LevelC::shutdown()
{
    delete mGameState.player;
    mGameState.player = nullptr;
    delete[] mGameState.enemies;
    mGameState.enemies = nullptr;
    delete[] mGameState.pickups;
    mGameState.pickups = nullptr;
    UnloadTexture(mGameState.bgTexture);
    UnloadTexture(mGameState.roadTexture);
    UnloadMusicStream(mGameState.bgm);
    UnloadSound(mGameState.collisionSound);
    UnloadSound(mGameState.pickupSound);
    UnloadSound(mGameState.sirenSound);
}
