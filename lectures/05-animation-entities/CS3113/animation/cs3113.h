#ifndef CS3113_H
#define CS3113_H
#define LOG(argument) std::cout << argument << '\n'

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>

enum AppStatus   { TERMINATED, RUNNING };
enum TextureType { SINGLE, ATLAS       };
enum Direction { LEFT, UP, RIGHT, DOWN }; // For walking


Color ColorFromHex(const char *hex);
void Normalise(Vector2 *vector);
float GetLength(const Vector2 *vector);

#endif // CS3113_H