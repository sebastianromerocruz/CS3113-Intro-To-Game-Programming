#include "Entity.h"

Entity::Entity() : mPosition {0.0f, 0.0f}, mMovement {0.0f, 0.0f},
                   mScale {DEFAULT_SIZE, DEFAULT_SIZE},
                   mColliderDimensions {DEFAULT_SIZE, DEFAULT_SIZE}, 
                   mTexture {NULL}, mTextureType {SINGLE}, 
                   mSpriteSheetDimensions {}, mDirection {DOWN}, 
                   mAnimationAtlas {{}}, mAnimationIndices {}, mFrameSpeed {0} {}

Entity::Entity(Vector2 position, Vector2 scale, const char *textureFilepath) : 
    mPosition {position}, mScale {scale}, mMovement {0.0f, 0.0f},
    mColliderDimensions {scale}, mTexture {LoadTexture(textureFilepath)},
    mTextureType {SINGLE}, mDirection {DOWN}, mAnimationAtlas {{}}, 
    mAnimationIndices {}, mFrameSpeed {0}, mSpeed {DEFAULT_SPEED}, 
    mAngle {0.0f} {}

Entity::Entity(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions, std::map<Direction, 
        std::vector<int>> animationAtlas) : mPosition {position}, 
        mMovement { 0.0f, 0.0f }, mScale {scale}, mColliderDimensions {scale}, 
        mTexture {LoadTexture(textureFilepath)}, mTextureType {ATLAS}, 
        mSpriteSheetDimensions {spriteSheetDimensions}, 
        mAnimationAtlas {animationAtlas}, mDirection {DOWN}, 
        mAnimationIndices {animationAtlas.at(DOWN)}, 
        mFrameSpeed {DEFAULT_FRAME_SPEED}, mAngle { 0.0f }, 
        mSpeed { DEFAULT_SPEED } {}

Entity::~Entity() { UnloadTexture(mTexture); };

/**
 * Checks if two entities are colliding based on their positions and collider 
 * dimensions.
 * 
 * @param other represents another Entity with which you want to check for 
 * collision. It is a pointer to the Entity class.
 * 
 * @return returns `true` if the two entities are colliding based on their
 * positions and collider dimensions, and `false` otherwise.
 */
bool Entity::isColliding(Entity *other) const 
{
    float xDistance = fabs(mPosition.x - other->getPosition().x) - 
        ((mColliderDimensions.x + other->getColliderDimensions().x) / 2.0f);
    float yDistance = fabs(mPosition.y - other->getPosition().y) - 
        ((mColliderDimensions.y + other->getColliderDimensions().y) / 2.0f);

    if (xDistance < 0.0f && yDistance < 0.0f) return true;

    return false;
}

/**
 * Updates the current frame index of an entity's animation based on the 
 * elapsed time and frame speed.
 * 
 * @param deltaTime represents the time elapsed since the last frame update.
 */
void Entity::animate(float deltaTime)
{
    mAnimationTime += deltaTime;
    float framesPerSecond = 1.0f / mFrameSpeed;

    if (mAnimationTime >= framesPerSecond)
    {
        mAnimationTime = 0.0f;

        mCurrentFrameIndex++;
        mCurrentFrameIndex %= mAnimationIndices.size();
    }
}

void Entity::update(float deltaTime)
{
    mAnimationIndices = mAnimationAtlas.at(mDirection);

    mPosition = {
        mPosition.x + mSpeed * mMovement.x * deltaTime,
        mPosition.y + mSpeed * mMovement.y * deltaTime
    };

    if (mTextureType == ATLAS && GetLength(mMovement) != 0) 
        animate(deltaTime);
}

void Entity::render()
{
    Rectangle textureArea;

    switch (mTextureType)
    {
        case SINGLE:
            // Whole texture (UV coordinates)
            textureArea = {
                // top-left corner
                0.0f, 0.0f,

                // bottom-right corner (of texture)
                static_cast<float>(mTexture.width),
                static_cast<float>(mTexture.height)
            };
            break;
        case ATLAS:
            textureArea = getUVRectangle(
                &mTexture, 
                mAnimationIndices[mCurrentFrameIndex], 
                mSpriteSheetDimensions.x, 
                mSpriteSheetDimensions.y
            );
        
        default: break;
    }

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mScale.x),
        static_cast<float>(mScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        static_cast<float>(mScale.x) / 2.0f,
        static_cast<float>(mScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        mTexture, 
        textureArea, destinationArea, originOffset,
        mAngle, WHITE
    );
}