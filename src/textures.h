#include "raylib.h"
#include "types.h"
#pragma once

void load_textures(textures_t* textures);
void unload_textures(textures_t* textures);
Texture get_component_texture(component_t component, textures_t* textures);