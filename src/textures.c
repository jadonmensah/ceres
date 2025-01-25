#include "textures.h"
#include "types.h"

void load_textures(textures_t* textures)
{	
	textures->checker = LoadTexture("checker.png");    
}
void unload_textures(textures_t* textures) 
{
	UnloadTexture(textures->checker);
}