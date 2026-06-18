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
    float top  = mOrigin.y - mOverlayHeight / 2.0f; // Adjustment for some reason

    DrawRectangle(left,
                  top,
                  mOverlayWidth,
                  mOverlayHeight,
                  Fade(BLACK, mAlpha));
}

void Effects::update(float deltaTime, Vector2 *viewOffset)
{
    if (viewOffset != nullptr) mViewOffset = *viewOffset;

    float diagonalRatio = mMaxWindowDimensions.y / mMaxWindowDimensions.x;

    switch (mCurrentEffect)
    {
        case FADEIN:
            mAlpha -= mEffectSpeed * deltaTime;

            if (mAlpha <= TRANSPARENT)
            {
                mAlpha = TRANSPARENT;
                mCurrentEffect = NONE;
            }

            break;
        
        case FADEOUT:
            mAlpha += mEffectSpeed * deltaTime;

            if (mAlpha >= SOLID)
            {
                mAlpha = SOLID;
                mCurrentEffect = NONE;
            }

            break;

        case SHRINK:
            mOverlayHeight -= mEffectSpeed * SIZE_SPEED_MULTIPLIER * deltaTime * diagonalRatio;
            mOverlayWidth  -= mEffectSpeed * SIZE_SPEED_MULTIPLIER * deltaTime;

            if (mOverlayHeight <= 0.0f ||
                mOverlayWidth  <= 0.0f)
            {
                mOverlayHeight = 0.0f;
                mOverlayWidth  = 0.0f;
                mCurrentEffect = NONE;
            }
            break;

        case GROW:
            mOverlayHeight += mEffectSpeed * SIZE_SPEED_MULTIPLIER * deltaTime * diagonalRatio;
            mOverlayWidth  += mEffectSpeed * SIZE_SPEED_MULTIPLIER * deltaTime;

            if (mOverlayHeight >= mMaxWindowDimensions.y ||
                mOverlayWidth  >= mMaxWindowDimensions.x)
            {
                mOverlayHeight = mMaxWindowDimensions.y;
                mOverlayWidth  = mMaxWindowDimensions.x;
                mCurrentEffect = NONE;
            }
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
            mAlpha = SOLID;
            break;

        case FADEOUT:
            mAlpha = TRANSPARENT;
            break;

        case SHRINK:
            mOverlayHeight = mMaxWindowDimensions.y;
            mOverlayWidth  = mMaxWindowDimensions.x;
            break;

        case GROW:
            mOverlayHeight = 0.0f;
            mOverlayWidth  = 0.0f;
            break;

        case NONE:
        default:
            break;
    }
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