#include "Dungeon.h"

Dungeon::Dungeon()                                      : Scene { {0.0f}, nullptr   } {}
Dungeon::Dungeon(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

Dungeon::~Dungeon() { shutdown(); }

void Dungeon::initialise()
{
   mGameState.nextSceneID = 0;

   mGameState.bgm = LoadMusicStream("assets/game/04 - Silent Forest.wav");
   SetMusicVolume(mGameState.bgm, 0.33f);
   PlayMusicStream(mGameState.bgm);

   /*
      ----------- MAP -----------
   */
   mGameState.map = new Map(
      LEVEL_WIDTH, LEVEL_HEIGHT,
      (unsigned int *) mLevelData,
      "assets/game/tileset.png",
      TILE_DIMENSION,
      4, 1,
      mOrigin
   );

   /*
      ----------- PROTAGONIST -----------
   */
   std::map<Animation, std::vector<int>> hinakoAnimationAtlas = 
   {
      {WALK_LEFT,  { 1, 2, 3, 4, 5, 6, 7, 8 }},
      {WALK_RIGHT, { 1, 2, 3, 4, 5, 6, 7, 8 }},
      {IDLE_LEFT,  { 1, 2, 3, 4, 5, 6 }      },
      {IDLE_RIGHT, { 1, 2, 3, 4, 5, 6 }      },
      {CHARGING,   { 1, 2, 3, 4, 5}          }
   };

   std::map<Animation, std::string> hinakoTextures = 
   {
      {WALK_LEFT,  "assets/game/Blue_witch/B_witch_run_left.png"  },
      {WALK_RIGHT, "assets/game/Blue_witch/B_witch_run_right.png" },
      {IDLE_LEFT,  "assets/game/Blue_witch/B_witch_idle_left.png" },
      {IDLE_RIGHT, "assets/game/Blue_witch/B_witch_idle_right.png"},
      {CHARGING,   "assets/game/Blue_witch/B_witch_charge.png"    },
   };

   std::map<Animation, Vector2> hinakoSpritesheetDimensions = 
   {
      {WALK_LEFT,  { 8, 1 }},
      {WALK_RIGHT, { 8, 1 }},
      {IDLE_LEFT,  { 6, 1 }},
      {IDLE_RIGHT, { 6, 1 }},
      {CHARGING,   { 5, 1 }}
   };

   float sizeRatio  = 48.0f / 64.0f;

   // Assets from @see https://sscary.itch.io/the-adventurer-female
   mGameState.hinako = new Entity(
      {mOrigin.x, mOrigin.y - 200.0f},
      {250.0f * sizeRatio, 250.0f},
      hinakoTextures,
      ATLAS,
      hinakoSpritesheetDimensions,
      hinakoAnimationAtlas,
      PLAYER
   );

   mGameState.hinako->setJumpingPower(550.0f);
   mGameState.hinako->setColliderDimensions({
      mGameState.hinako->getScale().x / 1.5f,
      mGameState.hinako->getScale().y / 1.5f
   });
   mGameState.hinako->setAcceleration({0.0f, ACCELERATION_OF_GRAVITY});
   mGameState.hinako->setFrameSpeed(Entity::DEFAULT_FRAME_SPEED / 2);

}

void Dungeon::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);

   mGameState.hinako->update(
      deltaTime,      // delta time / fixed timestep
      nullptr,        // player
      mGameState.map, // map
      nullptr,        // collidable entities
      0               // col. entity count
   );

}

void Dungeon::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   mGameState.map->render();
   mGameState.hinako->render();
}

void Dungeon::shutdown()
{
   delete mGameState.hinako;
   delete mGameState.map;

   UnloadMusicStream(mGameState.bgm);
}