#include "raylib.h"
#include "types.h"
#include "input.h"
#include <stdio.h>
#include "draw.h"

int get_snapped_mouse_x () 
{
	return ((GetMouseX() / 50) * 50) + 25;
}

int get_snapped_mouse_y ()
{
	return ((GetMouseY() / 50) * 50) + 25;
}

int get_cursor_grid_index ()
{
	return ((GetMouseY() / 50) * 24) + (GetMouseX() / 50);
}

int coords_to_grid_index(Vector2 coords) {
	int res = (((int)coords.y / 50) * 24) + ((int)coords.x / 50);
	return res;
}

Vector2 grid_index_to_coords(int i) {
	return (Vector2){(i % 24)*50+25, (i/24)*50+25};
}

int wire_next_cell(int cell, Vector2 anchor, Vector2 end, bool met_anchor) {
	Vector2 cell_coords = grid_index_to_coords(cell);
	// if not already past anchor move towards anchor and return
	if (!met_anchor) {
		return coords_to_grid_index(Vector2MoveTowards(cell_coords, anchor, 50));
	} else {
		return coords_to_grid_index(Vector2MoveTowards(cell_coords, end, 50));
	}
}

void handle_inputs(app_state_t* app_state)
{
	if (IsKeyDown(KEY_X))
	{
		app_state->input_mode = IM_DELETE;
	}

	if (IsKeyDown(KEY_W))
	{
		app_state->input_mode = IM_WIRE;
	}

	if (IsKeyDown(KEY_R))
	{
		app_state->input_mode = IM_RESISTOR;
	}

	if (IsKeyDown(KEY_C))
	{
		app_state->input_mode = IM_CAPACITOR;
	}

	if (IsKeyDown(KEY_L))
	{
		app_state->input_mode = IM_INDUCTOR;
	}

	if (IsKeyDown(KEY_I))
	{
		app_state->input_mode = IM_ISOURCE;
	}

	if (IsKeyDown(KEY_V))
	{
		app_state->input_mode = IM_VSOURCE;
	}

	if (IsKeyDown(KEY_G))
	{
		app_state->input_mode = IM_GROUND;
	}

	if (IsKeyDown(KEY_M))
	{
		app_state->input_mode = IM_MEASURE;
	}

	if (IsKeyPressed(KEY_UP) ||  IsKeyPressed(KEY_RIGHT)) {
		app_state->component_rotation = (app_state->component_rotation + 1) % 4;
	}

	if (IsKeyPressed(KEY_DOWN) ||IsKeyPressed(KEY_LEFT)) {
		app_state->component_rotation = (app_state->component_rotation - 1) % 4;
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && app_state->input_mode == IM_WIRE && !app_state->dragging_wire)
	{
		app_state->wire_drag_start.x = get_snapped_mouse_x();
		app_state->wire_drag_start.y = get_snapped_mouse_y();
		app_state->dragging_wire = true;
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && app_state->dragging_wire)
	{
		app_state->wire_drag_end.x = get_snapped_mouse_x();
		app_state->wire_drag_end.y = get_snapped_mouse_y();
		
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && app_state->dragging_wire)
	{
		app_state->dragging_wire = false;
		Vector2 anchor = get_anchor(app_state->wire_drag_start, app_state->wire_drag_end);
		bool met_anchor = false;
		bool not_at_end = true;
		int i = 0;
		for(int cell = coords_to_grid_index(app_state->wire_drag_start); not_at_end; cell = wire_next_cell(cell, anchor, app_state->wire_drag_end, met_anchor)) {
			
			if (cell == coords_to_grid_index(anchor)) met_anchor = true;
			if (cell == coords_to_grid_index(app_state->wire_drag_end)) not_at_end = false; // so that the final wire cell is still drawn
			render_info_t render_info;
			render_info.active = true;
			render_info.component = (component_t)(app_state->input_mode);
			render_info.rotation = app_state->component_rotation;
			app_state->component_grid[cell] = render_info;
			// failsafe so that we don't go on forever if the algorithm is buggy
			i++;
			if (i > 100) {printf("max its exceeded\n"); break;}
		}
		
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && app_state->input_mode == IM_DELETE)
	{
		app_state->component_grid[get_cursor_grid_index()].active = false;
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_placement_mode(app_state->input_mode))
	{
		if (!app_state->component_grid[get_cursor_grid_index()].active) {	
			render_info_t render_info;
			render_info.active = true;
			render_info.component = (component_t)(app_state->input_mode);
			render_info.rotation = app_state->component_rotation;
			app_state->component_grid[get_cursor_grid_index()] = render_info;
		}
	}
	
    
}