#include "raylib.h"
#include "raymath.h"
#include "types.h" // custom types & functions for dealing with them
#include "init.h" // initialisation functions
#include "textures.h" // texture loading
#include "input.h" // input handling
#include "draw.h" // frame drawing
#include <stdio.h>

// TODO: GUI: wire persistence, wires extend to component terminals, measure/multimeter mode
// TODO: component grid to circuit MNA matrix & solve circuit
// TODO: 

int main()
{

	SetConfigFlags( FLAG_VSYNC_HINT );

	InitWindow(1200, 800, "ceres");

	app_state_t app_state;
	init_app_state(&app_state);

	textures_t textures;
	load_textures(&textures);

	while (!WindowShouldClose())
	{
		
		handle_inputs(&app_state);
		BeginDrawing();
		ClearBackground(BLACK);
		draw_app(&app_state, &textures);		
		EndDrawing();
	}

	unload_textures(&textures);
	CloseWindow();
	return 0;
}
