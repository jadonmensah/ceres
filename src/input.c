#include "raylib.h"
#include "types.h"
#include "input.h"
#include <stdio.h>

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
	printf("%d\n", ((GetMouseY() / 50) * 24) + (GetMouseX() / 50) );
	return ((GetMouseY() / 50) * 24) + (GetMouseX() / 50);
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

	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) ||  IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
		app_state->component_rotation = !app_state->component_rotation; // rotational symmetry
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
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && app_state->input_mode == IM_DELETE)
	{
		// TODO implement me!
		// Look up component at mouse position
		// Clear screen area covered by component
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_placement_mode(app_state->input_mode))
	{
		render_info_t render_info;
		render_info.active = true;
		render_info.component = (component_t)(app_state->input_mode);
		render_info.position.x = get_snapped_mouse_x();
		render_info.position.y = get_snapped_mouse_y();
		render_info.rotation = app_state->component_rotation;
		app_state->component_grid[get_cursor_grid_index()] = render_info;
	}
}