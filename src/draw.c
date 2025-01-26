#include "raylib.h"
#include "types.h"
#include "input.h"
#include "textures.h"
#include "DrawTextureTiled.h"
#include "draw.h"
#include <stdio.h>

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

void draw_status_bar(app_state_t* app_state) {
		Rectangle status_bar_background = {.x = 0, .y = 750, .width = 1200, .height=50};
		DrawRectangleRec(status_bar_background, DARKGRAY);
		
        DrawText((char *)(&(app_state->input_mode)), 25, 765, 20, WHITE);

        char fps_str[8];
        sprintf(fps_str, "%d fps", GetFPS());
        DrawText(fps_str, 60, 765, 20, WHITE);
}

void draw_wire(Vector2 start, Vector2 end) {
    // swap anchors to produce opposite snapping
    // for later - experiment with other types of snapping
    Vector2 delta = Vector2Subtract(end, start);
    Vector2 anchor;
    if ((delta.x > 0 && delta.y <= 0 ) || (delta.y > 0 && delta.x <= 0 )) 
    {
        anchor = (Vector2){start.x, end.y}; 
    } 
    else 
    {
           
        anchor = (Vector2){end.x, start.y};
    }
    DrawLineEx(Vector2AddValue(start, 3), Vector2AddValue(anchor, 3), 5, HOVER_SHADOW);
    DrawLineEx(Vector2AddValue(anchor, 3), Vector2AddValue(end, 3), 5, HOVER_SHADOW);
    DrawLineEx(start, anchor, 5, LIGHTGRAY);
    DrawLineEx(anchor, end, 5, LIGHTGRAY);
}

void draw_component(Texture component, Vector2 position, bool rotation) {

    DrawTexturePro(component, (Rectangle){0.0f, 0.0f, component.width, component.height}, 
    (Rectangle){position.x+3, position.y+3, component.width, component.height}, 
    (Vector2){(component.width / 2.0f), (component.height / 2.0f)},
    rotation*90.0f,
    HOVER_SHADOW
    );

    DrawTexturePro(component, (Rectangle){0.0f, 0.0f, component.width, component.height}, 
    (Rectangle){position.x, position.y, component.width, component.height}, 
    (Vector2){(component.width / 2.0f), (component.height / 2.0f)},
    rotation*90.0f,
    LIGHTGRAY
    );
}

void draw_component_grid(render_info_t* component_grid, textures_t* textures) {
    for (int i = 0; i < SZ_COMPONENT_GRID; i++) {
        if (component_grid[i].active) {
            draw_component(
            get_component_texture(component_grid[i].component, textures), 
            (Vector2){(i % 24)*50+25,(i/24)*50+25}, 
            component_grid[i].rotation); 
        }  
    }
}

void draw_app(app_state_t* app_state, textures_t* textures) {
		draw_tiling_background(textures->checker, textures->noise);

		if (app_state->dragging_wire)
		{
			draw_wire(app_state->wire_drag_start, app_state->wire_drag_end);
		}
        

        if (app_state->input_mode == IM_VSOURCE) {
            // use vsource as cursor
            draw_component(textures->vsource, (Vector2){get_snapped_mouse_x(), get_snapped_mouse_y()}, app_state->component_rotation);
        }

        if (app_state->input_mode == IM_ISOURCE) {
            // use isource as cursor
            draw_component(textures->isource, (Vector2){get_snapped_mouse_x(), get_snapped_mouse_y()}, app_state->component_rotation);
        }

        draw_component_grid(app_state->component_grid, textures);

        draw_status_bar(app_state);
}