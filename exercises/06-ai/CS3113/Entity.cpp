#include "Entity.h"

Entity::Entity() : mPosition {0.0f, 0.0f}, mMovement {0.0f, 0.0f},
                   mVelocity {0.0f, 0.0f}, mAcceleration {0.0f, 0.0f},
                   mScale {DEFAULT_SIZE, DEFAULT_SIZE},
                   mColliderDimensions {DEFAULT_SIZE, DEFAULT_SIZE},
                   mTexture {NULL}, mTextureType {SINGLE}, mAngle {0.0f},
                   mSpriteSheetDimensions {}, mDirection {RIGHT},
                   mAnimationAtlas {{}}, mAnimationIndices {}, mFrameSpeed {0},
                   mEntityType {NONE} { }

Entity::Entity(Vector2 position, Vector2 scale, const char *textureFilepath,
    EntityType entityType) : mPosition {position}, mVelocity {0.0f, 0.0f},
    mAcceleration {0.0f, 0.0f}, mScale {scale}, mMovement {0.0f, 0.0f},
    mColliderDimensions {scale}, mTexture {LoadTexture(textureFilepath)},
    mTextureType {SINGLE}, mDirection {RIGHT}, mAnimationAtlas {{}},
    mAnimationIndices {}, mFrameSpeed {0}, mSpeed {DEFAULT_SPEED},
    mAngle {0.0f}, mEntityType {entityType} { }

Entity::Entity(Vector2 position, Vector2 scale, const char *textureFilepath,
        TextureType textureType, Vector2 spriteSheetDimensions, std::map<Direction,
        std::vector<int>> animationAtlas, EntityType entityType) :
        mPosition {position}, mVelocity {0.0f, 0.0f},
        mAcceleration {0.0f, 0.0f}, mMovement { 0.0f, 0.0f }, mScale {scale},
        mColliderDimensions {scale}, mTexture {LoadTexture(textureFilepath)},
        mTextureType {ATLAS}, mSpriteSheetDimensions {spriteSheetDimensions},
        mAnimationAtlas {animationAtlas}, mDirection {RIGHT},
        mAnimationIndices {animationAtlas.at(RIGHT)},
        mFrameSpeed {DEFAULT_FRAME_SPEED}, mAngle { 0.0f },
        mSpeed { DEFAULT_SPEED }, mEntityType {entityType} { }

Entity::~Entity() { UnloadTexture(mTexture); };

void Entity::checkCollisionY(Entity *collidableEntities, int collisionCheckCount)
{
    for (int i = 0; i < collisionCheckCount; i++)
    {
        Entity *collidableEntity = &collidableEntities[i];

        if (isColliding(collidableEntity))
        {
            float yDistance = fabs(mPosition.y - collidableEntity->mPosition.y);
            float yOverlap  = fabs(yDistance - (mColliderDimensions.y / 2.0f) -
                              (collidableEntity->mColliderDimensions.y / 2.0f));

            if (mVelocity.y > 0)
            {
                mPosition.y -= yOverlap;
                mVelocity.y  = 0;
                mIsCollidingBottom = true;
            } else if (mVelocity.y < 0)
            {
                mPosition.y += yOverlap;
                mVelocity.y  = 0;
                mIsCollidingTop = true;

                if (collidableEntity->mEntityType == BLOCK)
                    collidableEntity->deactivate();
            }
        }
    }
}

void Entity::checkCollisionX(Entity *collidableEntities, int collisionCheckCount)
{
    for (int i = 0; i < collisionCheckCount; i++)
    {
        Entity *collidableEntity = &collidableEntities[i];

        if (isColliding(collidableEntity))
        {
            float yDistance = fabs(mPosition.y - collidableEntity->mPosition.y);
            float yOverlap  = fabs(yDistance - (mColliderDimensions.y / 2.0f) - (collidableEntity->mColliderDimensions.y / 2.0f));

            if (yOverlap < Y_COLLISION_THRESHOLD) continue;

            float xDistance = fabs(mPosition.x - collidableEntity->mPosition.x);
            float xOverlap  = fabs(xDistance - (mColliderDimensions.x / 2.0f) - (collidableEntity->mColliderDimensions.x / 2.0f));

            if (mVelocity.x > 0) {
                mPosition.x     -= xOverlap;
                mVelocity.x      = 0;
                mIsCollidingRight = true;
            } else if (mVelocity.x < 0) {
                mPosition.x    += xOverlap;
                mVelocity.x     = 0;
                mIsCollidingLeft = true;
            }
        }
    }
}

bool Entity::isColliding(Entity *other) const
{
    if (!other->isActive() || other == this) return false;

    float xDistance = fabs(mPosition.x - other->getPosition().x) -
        ((mColliderDimensions.x + other->getColliderDimensions().x) / 2.0f);
    float yDistance = fabs(mPosition.y - other->getPosition().y) -
        ((mColliderDimensions.y + other->getColliderDimensions().y) / 2.0f);

    if (xDistance < 0.0f && yDistance < 0.0f) return true;

    return false;
}

void Entity::animate(float deltaTime)
{
    mAnimationIndices = mAnimationAtlas.at(mDirection);

    mAnimationTime += deltaTime;
    float framesPerSecond = 1.0f / mFrameSpeed;

    if (mAnimationTime >= framesPerSecond)
    {
        mAnimationTime = 0.0f;

        mCurrentFrameIndex++;
        mCurrentFrameIndex %= mAnimationIndices.size();
    }
}

void Entity::AIWander() { moveLeft(); }

void Entity::AIFollow(Entity *target)
{
    switch (mAIState)
    {
    case IDLE:
        if (Vector2Distance(mPosition, target->getPosition()) < 250.0f)
            mAIState = WALKING;
        break;

    case WALKING:
        if (mPosition.x > target->getPosition().x) moveLeft();
        else                                       moveRight();

    default:
        break;
    }
}

/**
 * TODO: Implement this method.
 *
 * Use linear interpolation to smoothly move this entity's position toward the
 * target's position each frame. Your implementation should use a two-state FSM
 * (IDLE and FOLLOWING), consistent with the other AI methods in this file.
 *
 * Recall that lerp(a, b, t) = a + (b - a) * t
 */
void Entity::AILerp(Entity *target, float deltaTime)
{
    // Your code goes here.
}

void Entity::AIActivate(Entity *target, float deltaTime)
{
    switch (mAIType)
    {
    case WANDERER:
        AIWander();
        break;

    case FOLLOWER:
        AIFollow(target);
        break;

    case LERPER:
        AILerp(target, deltaTime);
        break;

    default:
        break;
    }
}

void Entity::update(float deltaTime, Entity *player, Entity *collidableEntities,
    int collisionCheckCount, Entity* blocks, int blockCount)
{
    if (mEntityStatus == INACTIVE) return;

    if (mEntityType == NPC) AIActivate(player, deltaTime);

    resetColliderFlags();

    // LERPER entities move via direct position manipulation inside AILerp,
    // so we skip the standard velocity / collision pipeline for them.
    if (mAIType != LERPER)
    {
        mVelocity.x = mMovement.x * mSpeed;

        mVelocity.x += mAcceleration.x * deltaTime;
        mVelocity.y += mAcceleration.y * deltaTime;

        if (mIsJumping)
        {
            mIsJumping = false;
            mVelocity.y -= mJumpingPower;
        }

        mPosition.y += mVelocity.y * deltaTime;
        checkCollisionY(collidableEntities, collisionCheckCount);
        checkCollisionY(blocks, blockCount);

        mPosition.x += mVelocity.x * deltaTime;
        checkCollisionX(collidableEntities, collisionCheckCount);
        checkCollisionX(blocks, blockCount);
    }

    if (mTextureType == ATLAS)
    {
        // LERPER entities always animate; others only animate while grounded and moving
        bool shouldAnimate = (mAIType == LERPER) ||
                             (GetLength(mMovement) != 0 && mIsCollidingBottom);
        if (shouldAnimate) animate(deltaTime);
    }
}

void Entity::render()
{
    if(mEntityStatus == INACTIVE) return;

    Rectangle textureArea;

    switch (mTextureType)
    {
        case SINGLE:
            textureArea = {
                0.0f, 0.0f,
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

    Rectangle destinationArea = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mScale.x),
        static_cast<float>(mScale.y)
    };

    Vector2 originOffset = {
        static_cast<float>(mScale.x) / 2.0f,
        static_cast<float>(mScale.y) / 2.0f
    };

    DrawTexturePro(
        mTexture,
        textureArea, destinationArea, originOffset,
        mAngle, WHITE
    );

    // displayCollider();
}

void Entity::displayCollider()
{
    Rectangle colliderBox = {
        mPosition.x - mColliderDimensions.x / 2.0f,
        mPosition.y - mColliderDimensions.y / 2.0f,
        mColliderDimensions.x,
        mColliderDimensions.y
    };

    DrawRectangleLines(
        colliderBox.x,
        colliderBox.y,
        colliderBox.width,
        colliderBox.height,
        GREEN
    );
}
