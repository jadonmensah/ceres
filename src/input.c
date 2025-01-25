#include "raylib.h"
#include "types.h"
#include "input.h"

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

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && app_state->input_mode == IM_WIRE && !app_state->dragging_wire)
	{
		app_state->wire_drag_start.x = GetMouseX();
		app_state->wire_drag_start.y = GetMouseY();
		app_state->dragging_wire = true;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && app_state->dragging_wire)
	{
		app_state->wire_drag_end.x = GetMouseX();
		app_state->wire_drag_end.y = GetMouseY();
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
		render_info.component = (component_t)(app_state->input_mode);
		render_info.position.x = GetMouseX();
		render_info.position.y = GetMouseY();
		// enqueue(render_info, app_state.render_queue, &app_state.head_render_queue, &app_state.tail_render_queue, SZ_RENDER_QUEUE);
	}
}