#include "LevelB.h"

#ifndef LEVELC_H
#define LEVELC_H

class LevelC : public Scene {
public:
    static constexpr float TARGET_DISTANCE = 2500.0f,
                           BASE_SCROLL     = 380.0f;

    LevelC();
    LevelC(Vector2 origin, const char *bgHexCode);
    ~LevelC();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif
