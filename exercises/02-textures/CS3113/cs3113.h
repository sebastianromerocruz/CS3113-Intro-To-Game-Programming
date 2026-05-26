#ifndef CS3113_H
#define CS3113_H
#define LOG(argument) std::cout << argument << '\n'

#include "raylib.h"
#include <stdio.h>

enum AppStatus { TERMINATED, RUNNING };

Color ColorFromHex(const char *hex);

#endif // CS3113_H