#include "Effects.h"

Effects::Effects(Vector2 origin, float windowWidth, float windowHeight) : mAlpha{SOLID},
                     mEffectSpeed{DEFAULT_SPEED},
                     mOverlayWidth{windowWidth},
                     mOverlayHeight{windowHeight}, mCurrentEffect{NONE},
                     mViewOffset{{}}, mOrigin{origin},
                     mMaxWindowDimensions{windowWidth, windowHeight}
{
}

void Effects::drawOverlay()
{
    float left = mViewOffset.x - mOverlayWidth  / 2.0f;
    float top  = mOrigin.y - mOverlayHeight / 2.0f;

    DrawRectangle(left,
                  top,
                  mOverlayWidth,
                  mOverlayHeight,
                  Fade(BLACK, mAlpha));
}

void Effects::render()
{
    switch (mCurrentEffect)
    {
        case FADEIN:
        case FADEOUT:
        case SHRINK:
        case GROW:
            drawOverlay();
            break;

        case NONE:

    default:
        break;
    }
}

void Effects::start(EffectType effectType)
{
    mCurrentEffect = effectType;

    switch (mCurrentEffect)
    {
        case FADEIN:
            // TODO: Set mAlpha to its starting value for a fade-in
            break;

        case FADEOUT:
            // TODO: Set mAlpha to its starting value for a fade-out
            break;

        case SHRINK:
            // TODO: Set overlay dimensions to their starting values for a shrink
            break;

        case GROW:
            // TODO: Set overlay dimensions to their starting values for a grow
            break;

        case NONE:
        default:
            break;
    }
}

void Effects::update(float deltaTime, Vector2 *viewOffset)
{
    if (viewOffset != nullptr) mViewOffset = *viewOffset;

    float diagonalRatio = mMaxWindowDimensions.y / mMaxWindowDimensions.x;

    switch (mCurrentEffect)
    {
        case FADEIN:
            // TODO: Decrease mAlpha over time using mEffectSpeed and deltaTime.
            //       Once it reaches TRANSPARENT, clamp it and set mCurrentEffect to NONE.
            break;

        case FADEOUT:
            // TODO: Increase mAlpha over time using mEffectSpeed and deltaTime.
            //       Once it reaches SOLID, clamp it and set mCurrentEffect to NONE.
            break;

        case SHRINK:
            // TODO: Decrease mOverlayWidth and mOverlayHeight over time.
            //       Use SIZE_SPEED_MULTIPLIER and diagonalRatio to keep the shrink uniform.
            //       Once either dimension reaches 0, clamp both to 0 and set mCurrentEffect to NONE.
            break;

        case GROW:
            // TODO: Increase mOverlayWidth and mOverlayHeight over time.
            //       Use SIZE_SPEED_MULTIPLIER and diagonalRatio to keep the growth uniform.
            //       Once either dimension reaches its max, clamp both and set mCurrentEffect to NONE.
            break;

        case NONE:
        default:
            break;
    }
}
