#include "raylib.h"
#include "types.h"
#include "DrawTextureTiled.h"
#pragma once

void draw_tiling_background(Texture tile);

void draw_status_bar(app_state_t app_state);

void draw_app(app_state_t app_state, textures_t textures);
