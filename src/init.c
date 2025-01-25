#include "init.h"
#include "types.h"
#include "raylib.h"

void init_app_state(app_state_t* app_state)
{
	app_state->input_mode = IM_WIRE;
	app_state->dragging_wire = false;
	app_state->wire_drag_start.x = 0;
	app_state->wire_drag_start.y = 0;
	app_state->wire_drag_end.x = 0;
	app_state->wire_drag_end.y = 0;
	memset(app_state->render_queue, 0, SZ_RENDER_QUEUE); // Circular queue
	app_state->head_render_queue = -1;
	app_state->tail_render_queue = 0;
}
