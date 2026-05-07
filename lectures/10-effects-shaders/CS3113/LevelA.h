#include "Scene.h"

#ifndef LEVELA_H
#define LEVELA_H

constexpr int LEVEL_WIDTH  = 14;
constexpr int LEVEL_HEIGHT = 8;

class LevelA : public Scene {
private:
    unsigned int mLevelData[LEVEL_WIDTH * LEVEL_HEIGHT];

public:
    static constexpr float TILE_DIMENSION  = 75.0f,
                           TARGET_DISTANCE = 1500.0f,
                           BASE_SCROLL     = 280.0f;

    LevelA();
    LevelA(Vector2 origin, const char *bgHexCode);
    ~LevelA();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif
