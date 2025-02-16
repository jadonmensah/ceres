#include "raylib.h"
#include "types.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

int get_snapped_mouse_x () 
{
	int res = (((GetMouseX() / 50) * 50) + 25 );
	if (res < 0) {
		res = 25;
	}
	if (res > 1200) {
		res = 1175;
	}
	return res;
}

int get_snapped_mouse_y ()
{
	int res = (((GetMouseY() / 50) * 50) + 25);
	if (res < 0) {
		res = 25;
	}
	if (res > 750) {
		res = 725;
	}
	return res;
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

char get_quadrant(Vector2 v) {
	if (v.x > 0 && v.y > 0) {
		return 0;
	} if (v.x <= 0 && v.y > 0) {
		return 1;
	} if (v.x <= 0 && v.y <= 0) {
		return 2;
	} if (v.x > 0 && v.y <= 0) {
		return 3;
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
		// Attempt to simulate circuit. For now just dummy run ngspice
		system("ngspice_con.exe -p -b rc-meas-ac.sp > plswork.txt");
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
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && app_state->dragging_wire) // this part is slowly becoming cursed you should fix it
	{
		
		app_state->dragging_wire = false;
		Vector2 anchor = get_anchor(app_state->wire_drag_start, app_state->wire_drag_end);
		bool met_anchor = false;
		bool not_at_end = true;
		char rotation  = 0;
		// if the anchor and the start are the same then rotation should be determined based on end point and not anchor
		if (coords_to_grid_index(anchor) == coords_to_grid_index(app_state->wire_drag_start)) {
			if (app_state->wire_drag_end.x == app_state->wire_drag_start.x) {
				rotation = 1;
			}
		}
		else if (anchor.x == app_state->wire_drag_start.x) {
			rotation = 1;
		}
		int i = 0;
		for(int cell = coords_to_grid_index(app_state->wire_drag_start); not_at_end; cell = wire_next_cell(cell, anchor, app_state->wire_drag_end, met_anchor)) {
			
			if (cell == coords_to_grid_index(app_state->wire_drag_end)) not_at_end = false; // so that the final wire cell is still drawn
			if (cell == coords_to_grid_index(anchor) 
			&& coords_to_grid_index(anchor) != coords_to_grid_index(app_state->wire_drag_end)
			&& coords_to_grid_index(anchor) != coords_to_grid_index(app_state->wire_drag_start)) {
				met_anchor = true;
				render_info_t render_info;
				render_info.active = true;
				render_info.component = C_CORNER_WIRE;
				char quadrant_end = get_quadrant(Vector2Subtract(app_state->wire_drag_end, app_state->wire_drag_start));
				render_info.rotation = quadrant_end; // quadrant end is in wrt start is the rotation of this guy
				app_state->component_grid[cell] = render_info;
				rotation = (rotation + 1) % 2;
			} else {
				if (coords_to_grid_index(anchor) == coords_to_grid_index(app_state->wire_drag_start)) {
					met_anchor = true;
			}
			render_info_t render_info;
			render_info.active = true;
			
			// If we're overwriting another wire with different rotation and this is not the end/start, place an X junction
			if (app_state->component_grid[cell].active 
			&& (app_state->component_grid[cell].rotation == (rotation + 1)% 2)
			&& (app_state->component_grid[cell].component == C_WIRE || app_state->component_grid[cell].component == C_T_JUNCTION)
			&& not_at_end && cell != coords_to_grid_index(app_state->wire_drag_start)) {
				render_info.component = C_X_JUNCTION;
			}
			else if (app_state->component_grid[cell].active 
			&& (app_state->component_grid[cell].rotation == (rotation + 1)% 2)
			&& (app_state->component_grid[cell].component == C_WIRE
			&& (!not_at_end || cell == coords_to_grid_index(app_state->wire_drag_start))))
			{
				render_info.component = C_T_JUNCTION;
				if (app_state->component_grid[cell].rotation == 0) {
					if (anchor.y <= grid_index_to_coords(cell).y) {
						rotation = 1;
					} else {
						rotation = 3;
					}
				} else {
					if (anchor.x >= grid_index_to_coords(cell).x) {
						rotation = 2;
					} else {
						rotation = 0;
					}
				}
			}
			 
			else {
				render_info.component = (component_t)(app_state->input_mode);
			}
			render_info.rotation = rotation;
			app_state->component_grid[cell] = render_info;
			}
			
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