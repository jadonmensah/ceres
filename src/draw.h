#include "raylib.h"
#include "types.h"
#include "DrawTextureTiled.h"

#pragma once

void draw_app(app_state_t* app_state, textures_t* textures);
Vector2 get_anchor(Vector2 start, Vector2 end);
