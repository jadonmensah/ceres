// custom types, constants & functions to deal with them
#include "raylib.h"
#include "raymath.h"
#define SZ_RENDER_QUEUE 8
#pragma once

#define HOVER_SHADOW CLITERAL(Color){80, 80, 80, 190}


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

typedef struct
{
    Texture checker;
    Texture vsource;
    Texture noise;
    Texture isource;
} textures_t;

bool is_placement_mode(input_mode_t input_mode);