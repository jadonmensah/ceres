#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <string.h>
#define SZ_RENDER_QUEUE 8

typedef enum // characters for display purposes
{
	IM_WIRE = 'w',
	IM_RESISTOR = 'r',
	IM_CAPACITOR = 'c',
	IM_INDUCTOR = 'l',
	IM_ISOURCE = 'i',
	IM_VSOURCE = 'v',
	IM_GROUND = 'g',
	IM_MEASURE = 'm',
	IM_DELETE = 'x',
} input_mode_t;

typedef enum
{
	C_WIRE,
	C_RESISTOR,
	C_CAPACITOR,
	C_INDUCTOR,
	C_ISOURCE,
	C_VSOURCE,
	C_GROUND,
} component_t;

bool is_placement_mode(input_mode_t input_mode)
{
	switch (input_mode)
	{
	case IM_WIRE:
	case IM_MEASURE:
	case IM_DELETE:
		return false;
	default:
		return true;
	}
}

typedef struct
{
	component_t component;
	Vector2 position;
} render_info_t;

typedef struct
{
	input_mode_t input_mode;
	bool dragging_wire;
	Vector2 wire_drag_start;
	Vector2 wire_drag_end;
	render_info_t *render_queue[SZ_RENDER_QUEUE];
	int head_render_queue;
	int tail_render_queue;

} app_state_t;

void init_app_state(app_state_t *app_state)
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

void draw_status_bar(app_state_t* app_state) {
		Rectangle status_bar_background = {.x = 0, .y = 750, .width = 1200, .height=50};
		DrawRectangleRec(status_bar_background, RED);
		DrawText((char *)(&(app_state->input_mode)), 25, 765, 20, WHITE);
}

void draw_app(app_state_t* app_state) {
		// draw some text using the default font
		draw_status_bar(app_state);
	
		// draw based on app state
		if (app_state->dragging_wire)
		{
			DrawLineEx(app_state->wire_drag_start, app_state->wire_drag_end, 5, LIGHTGRAY);
		}
}

int main()
{

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1200, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	app_state_t app_state;
	init_app_state(&app_state);

	// game loop
	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// inputs -> change app state
		handle_inputs(&app_state);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// Draw app 
		draw_app(&app_state);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
