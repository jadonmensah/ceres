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
	memset(app_state->component_grid, 0, SZ_COMPONENT_GRID*sizeof(render_info_t));
}
