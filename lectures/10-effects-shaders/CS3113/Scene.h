#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"

constexpr int MAX_ENEMIES = 16;
constexpr int MAX_PICKUPS = 4;

struct GameState
{
    Entity *player;
    Entity *enemies;
    Entity *pickups;
    int enemyCount;
    int pickupCount;
    Map *map;
    int nextSceneID;

    int lives;
    float distanceTraveled;
    float targetDistance;
    float scrollSpeed;
    float invincibilityTimer;
    float spawnTimer;
    float pickupSpawnTimer;
    float roadScrollOffset;
    float blizzardIntensity;
    bool copCaught;

    Texture2D roadTexture;
    Texture2D bgTexture;

    Music bgm;
    Sound collisionSound;
    Sound pickupSound;
    Sound sirenSound;
};

class Scene 
{
protected:
    GameState mGameState;
    Vector2 mOrigin;
    const char *mBGColourHexCode = "#000000";
    bool mIsGameplay = true;
    
public:
    Scene();
    Scene(Vector2 origin, const char *bgHexCode);

    virtual void initialise() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;
    
    GameState&  getState()                        { return mGameState;       }
    Vector2     getOrigin()          const { return mOrigin;          }
    const char* getBGColourHexCode() const { return mBGColourHexCode; }
    bool        isGameplay()         const { return mIsGameplay;      }
};

#endif
