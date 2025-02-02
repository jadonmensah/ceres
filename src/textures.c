#include "textures.h"
#include "types.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir

void load_textures(textures_t* textures)
{	
    SearchAndSetResourceDir("resources");
	textures->checker = LoadTexture("checker.png");
    textures->vsource = LoadTexture("vsource.png");
    textures->isource = LoadTexture("isource.png");
    textures->resistor = LoadTexture("resistor.png");
    textures->capacitor = LoadTexture("capacitor.png");
    textures->ground = LoadTexture("ground.png");
    textures->inductor = LoadTexture("inductor.png");
    textures->wire_straight = LoadTexture("wire_straight.png");
    textures->noise = LoadTextureFromImage(GenImageWhiteNoise(1200, 750, 0.994f));
    textures->wire_corner = LoadTexture("wire_corner.png");
    textures->wire_tjunction = LoadTexture("wire_tjunction.png");
    textures->wire_xjunction = LoadTexture("wire_xjunction.png");
}

Texture get_component_texture(component_t component, textures_t* textures) {
    switch (component) {
        case C_ISOURCE:
            return textures->isource;
        case C_VSOURCE:
            return textures->vsource;
        case C_RESISTOR:
            return textures->resistor;
        case C_CAPACITOR:
            return textures->capacitor;
        case C_INDUCTOR:
            return textures->inductor;
        case C_GROUND:
            return textures->ground;
        case C_WIRE:
            return textures->wire_straight;
        case C_CORNER_WIRE:
            return textures->wire_corner;
        case C_T_JUNCTION:
            return textures->wire_tjunction;
        case C_X_JUNCTION:
            return textures->wire_xjunction;
    };
}

void unload_textures(textures_t* textures) 
{
	UnloadTexture(textures->checker);
    UnloadTexture(textures->vsource);
    UnloadTexture(textures->resistor);
    UnloadTexture(textures->inductor);
    UnloadTexture(textures->ground);
    UnloadTexture(textures->capacitor);
    UnloadTexture(textures->noise);
    UnloadTexture(textures->isource);
    UnloadTexture(textures->wire_straight);
    UnloadTexture(textures->wire_corner);

}