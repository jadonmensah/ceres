#include "raylib.h"
#include "types.h"
#include "DrawTextureTiled.h"
#include "draw.h"

void draw_tiling_background(Texture tile) {
	Rectangle source_rectangle = (Rectangle){0, 0, 50, 50};
	Rectangle dest_rectangle = (Rectangle){0, 0, 1200, 750};
	DrawTextureTiled(tile, source_rectangle, dest_rectangle, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, LIGHTGRAY);
}

void draw_status_bar(app_state_t app_state) {
		Rectangle status_bar_background = {.x = 0, .y = 750, .width = 1200, .height=50};
		DrawRectangleRec(status_bar_background, DARKGRAY);
		DrawText((char *)(&(app_state.input_mode)), 25, 765, 20, WHITE);
}

void draw_app(app_state_t app_state, textures_t textures) {
		draw_tiling_background(textures.checker);

		
	
		// draw based on app state
		if (app_state.dragging_wire)
		{
			DrawLineEx(app_state.wire_drag_start, app_state.wire_drag_end, 5, LIGHTGRAY);
		}

        draw_status_bar(app_state);
}