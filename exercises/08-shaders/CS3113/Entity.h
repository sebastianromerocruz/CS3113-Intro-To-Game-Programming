#ifndef ENTITY_H
#define ENTITY_H

#include "Map.h"

enum Animation    { WALK_LEFT, WALK_RIGHT, IDLE_LEFT, IDLE_RIGHT, CHARGING };
enum EntityStatus { ACTIVE, INACTIVE                    };
enum EntityType   { PLAYER, BLOCK, PLATFORM, NPC, EMPTY };
enum AIType       { WANDERER, FOLLOWER                  };
enum AIState      { WALKING, IDLE, FOLLOWING            };

class Entity
{
private:
    Vector2 mPosition;
    Vector2 mMovement;
    Vector2 mVelocity;
    Vector2 mAcceleration;

    Vector2 mScale;
    Vector2 mColliderDimensions;

    std::map<Animation, Texture2D> mTextures;
    Texture2D mCurrentTexture;
    TextureType mTextureType;

    std::map<Animation, Vector2> mSpriteSheetDimensions;
    Vector2 mCurrentSpriteSheetDimensions;
    
    std::map<Animation, std::vector<int>> mAnimationAtlas;
    std::vector<int> mAnimationIndices;
    Animation mAnimation;
    Animation mPreviousDirection;
    int mFrameSpeed;

    int mCurrentFrameIndex = 0;
    float mAnimationTime = 0.0f;

    bool mIsJumping = false;
    float mJumpingPower = 0.0f;

    int mSpeed;
    float mAngle;

    bool mIsCollidingTop    = false;
    bool mIsCollidingBottom = false;
    bool mIsCollidingRight  = false;
    bool mIsCollidingLeft   = false;

    EntityStatus mEntityStatus = ACTIVE;
    EntityType   mEntityType;

    AIType  mAIType;
    AIState mAIState;

    bool isColliding(Entity *other) const;

    void checkCollisionY(Entity *collidableEntities, int collisionCheckCount);
    void checkCollisionY(Map *map);

    void checkCollisionX(Entity *collidableEntities, int collisionCheckCount);
    void checkCollisionX(Map *map);
    
    void resetColliderFlags() 
    {
        mIsCollidingTop    = false;
        mIsCollidingBottom = false;
        mIsCollidingRight  = false;
        mIsCollidingLeft   = false;
    }

    void animate(float deltaTime);
    void AIActivate(Entity *target);
    void AIWander();
    void AIFollow(Entity *target);

public:
    static constexpr int   DEFAULT_SIZE          = 250;
    static constexpr int   DEFAULT_SPEED         = 200;
    static constexpr int   DEFAULT_FRAME_SPEED   = 14;
    static constexpr float Y_COLLISION_THRESHOLD = 0.5f;

    Entity();
    Entity(Vector2 position, Vector2 scale, const char *textureFilepath, 
        EntityType entityType);
    Entity(Vector2 position, Vector2 scale, std::map<Animation, std::string> textures, 
        TextureType textureType, std::map<Animation, Vector2> spriteSheetDimensions, 
        std::map<Animation, std::vector<int>> animationAtlas, 
        EntityType entityType);
    ~Entity();

    void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount);
    void render();
    void normaliseMovement() { Normalise(&mMovement); }

    void jump()             { mIsJumping = true;         }
    void activate()         { mEntityStatus  = ACTIVE;   }
    void deactivate()       { mEntityStatus  = INACTIVE; }
    void displayCollider();

    bool isActive() { return mEntityStatus == ACTIVE ? true : false; }

    void moveLeft()  { mMovement.x = -1; mAnimation = IDLE_LEFT;    }
    void moveRight() { mMovement.x =  1; mAnimation = IDLE_RIGHT;   }
    void charge()    { mAnimation = mAnimation == CHARGING ? 
                                    mPreviousDirection : CHARGING;  }

    void resetMovement() { mMovement = { 0.0f, 0.0f }; }

    Vector2     getPosition()              const { return mPosition;              }
    Vector2     getMovement()              const { return mMovement;              }
    Vector2     getVelocity()              const { return mVelocity;              }
    Vector2     getAcceleration()          const { return mAcceleration;          }
    Vector2     getScale()                 const { return mScale;                 }
    Vector2     getColliderDimensions()    const { return mScale;                 }
    Vector2     getCurrentSpriteSheetDimensions() const { return mCurrentSpriteSheetDimensions; }
    Texture2D   getCurrentTexture()        const { return mCurrentTexture;        }
    TextureType getTextureType()           const { return mTextureType;           }
    Animation   getAnimation()             const { return mAnimation;             }
    int         getFrameSpeed()            const { return mFrameSpeed;            }
    float       getJumpingPower()          const { return mJumpingPower;          }
    bool        isJumping()                const { return mIsJumping;             }
    int         getSpeed()                 const { return mSpeed;                 }
    float       getAngle()                 const { return mAngle;                 }
    EntityType  getEntityType()            const { return mEntityType;            }
    AIType      getAIType()                const { return mAIType;                }
    AIState     getAIState()               const { return mAIState;               }

    
    bool isCollidingTop()    const { return mIsCollidingTop;    }
    bool isCollidingBottom() const { return mIsCollidingBottom; }

    std::map<Animation, std::vector<int>> getAnimationAtlas() const { return mAnimationAtlas; }

    void setPosition(Vector2 newPosition)
        { mPosition = newPosition;                 }
    void setMovement(Vector2 newMovement)
        { mMovement = newMovement;                 }
    void setAcceleration(Vector2 newAcceleration)
        { mAcceleration = newAcceleration;         }
    void setScale(Vector2 newScale)
        { mScale = newScale;                       }
    // void setTexture(const char *textureFilepath)
    //     { mCurrentTexture = LoadTexture(textureFilepath); }
    void setColliderDimensions(Vector2 newDimensions) 
        { mColliderDimensions = newDimensions;     }
    void setSpriteSheetDimensions(Vector2 newDimensions) 
        { mCurrentSpriteSheetDimensions = newDimensions;  }
    void setSpeed(int newSpeed)
        { mSpeed  = newSpeed;                      }
    void setFrameSpeed(int newSpeed)
        { mFrameSpeed = newSpeed;                  }
    void setJumpingPower(float newJumpingPower)
        { mJumpingPower = newJumpingPower;         }
    void setAngle(float newAngle) 
        { mAngle = newAngle;                       }
    void setEntityType(EntityType entityType)
        { mEntityType = entityType;                }
    void setAnimation(Animation newDirection)
    { 
        mAnimation = newDirection;

        if (mTextureType == ATLAS) mAnimationIndices = mAnimationAtlas.at(mAnimation);
    }
    void setAIState(AIState newState)
        { mAIState = newState;                     }
    void setAIType(AIType newType)
        { mAIType = newType;                       }
};

#endif // ENTITY_CPP