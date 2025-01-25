#include "types.h"

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