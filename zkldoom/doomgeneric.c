#include "doomgeneric.h"

static uint32_t* DG_ScreenBuffer = 0;

void dg_Create()
{
	DG_ScreenBuffer = malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);
}

