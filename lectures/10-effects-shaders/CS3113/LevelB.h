#include "LevelA.h"

#ifndef LEVELB_H
#define LEVELB_H

class LevelB : public Scene {
public:
    static constexpr float TARGET_DISTANCE = 2000.0f,
                           BASE_SCROLL     = 340.0f;

    LevelB();
    LevelB(Vector2 origin, const char *bgHexCode);
    ~LevelB();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif
