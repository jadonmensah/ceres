// custom types, constants & functions to deal with them
#include "raylib.h"
#include "raymath.h"
#define SZ_COMPONENT_GRID 360 // 360 = 24 * 15 = (1200/50) * (750/50). Circuit area is 1200 by 750px
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

typedef enum // characters so we can cast between input_mode_t to component_t
{
    C_WIRE = 'w',
    C_CORNER_WIRE, // not directly placeable by user, used internally for drawing wires
    C_RESISTOR = 'r',
    C_CAPACITOR = 'c',
    C_INDUCTOR = 'l',
    C_ISOURCE = 'i',
    C_VSOURCE = 'v',
    C_GROUND = 'g',
    C_NULL = '-',
} component_t;

typedef struct
{
    bool active;
    component_t component;
    char rotation;
} render_info_t;

typedef struct
{
    input_mode_t input_mode;
    bool dragging_wire;
    Vector2 wire_drag_start;
    Vector2 wire_drag_end;
    render_info_t component_grid[SZ_COMPONENT_GRID];
    // 
    char component_rotation; 

} app_state_t;

typedef struct
{
    Texture checker;
    Texture vsource;
    Texture resistor;
    Texture capacitor;
    Texture ground;
    Texture inductor;
    Texture noise;
    Texture isource;
} textures_t;

bool is_placement_mode(input_mode_t input_mode);