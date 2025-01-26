#include "textures.h"
#include "types.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir

void load_textures(textures_t* textures)
{	
    SearchAndSetResourceDir("resources");
	textures->checker = LoadTexture("checker.png");
    textures->vsource = LoadTexture("vsource.png");
    textures->isource = LoadTexture("isource.png");
    textures->noise = LoadTextureFromImage(GenImageWhiteNoise(1200, 750, 0.994f));
}

Texture get_component_texture(component_t component, textures_t* textures) {
    switch (component) {
        case C_ISOURCE:
            return textures->isource;
        case C_VSOURCE:
            return textures->vsource;
    };
}

void unload_textures(textures_t* textures) 
{
	UnloadTexture(textures->checker);
    UnloadTexture(textures->vsource);
    UnloadTexture(textures->noise);
    UnloadTexture(textures->isource);
}