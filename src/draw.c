#include "raylib.h"
#include "types.h"
#include "DrawTextureTiled.h"
#include "draw.h"

void draw_tiling_background(Texture tile, Texture noise) {
	Rectangle source_rectangle = (Rectangle){0, 0, 50, 50};
	Rectangle dest_rectangle = (Rectangle){0, 0, 1200, 750};
	DrawTextureTiled(tile, source_rectangle, dest_rectangle, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, LIGHTGRAY);

    DrawTexture(noise, 0, 0, (Color){255,255,255,30});

    DrawRectangleGradientV(0, 700, 1200, 50, (Color){0,0,0,0}, (Color){0,0,0,30});
    DrawRectangleGradientV(0, 0, 1200, 100, (Color){230,230,230,30}, (Color){0,0,0,0});
    DrawRectangleGradientH(0, 0, 100, 750, (Color){230,230,230,30}, (Color){0,0,0,0});
    DrawRectangleGradientH(1150, 0, 50, 750, (Color){0,0,0,0}, (Color){0,0,0,30});
}

void draw_status_bar(app_state_t app_state) {
		Rectangle status_bar_background = {.x = 0, .y = 750, .width = 1200, .height=50};
		DrawRectangleRec(status_bar_background, DARKGRAY);
		DrawText((char *)(&(app_state.input_mode)), 25, 765, 20, WHITE);
}

void draw_wire(Vector2 start, Vector2 end) {
    // TODO change me so wires are parallel/perpendicular w/grid
    DrawLineEx(Vector2AddValue(start, 3), Vector2AddValue(end, 3), 5, HOVER_SHADOW);
    DrawLineEx(start, end, 5, LIGHTGRAY);
}

void draw_app(app_state_t app_state, textures_t textures) {
		draw_tiling_background(textures.checker, textures.noise);

		if (app_state.dragging_wire)
		{
			draw_wire(app_state.wire_drag_start, app_state.wire_drag_end);
		}
        
        if (app_state.input_mode == IM_VSOURCE) {
            // use vsource as cursor
            DrawTexture(textures.vsource, GetMouseX() - 22, GetMouseY() - 22, HOVER_SHADOW);
            DrawTexture(textures.vsource, GetMouseX() - 25, GetMouseY() - 25, LIGHTGRAY); 
        }

        if (app_state.input_mode == IM_ISOURCE) {
            // use vsource as cursor
            DrawTexture(textures.isource, GetMouseX() - 47, GetMouseY() - 22, HOVER_SHADOW);
            DrawTexture(textures.isource, GetMouseX() - 50, GetMouseY() - 25, LIGHTGRAY); 
        }


        draw_status_bar(app_state);
}