
#include <stddef.h>

#include "doomtype.h"
#include "doomdef.h"
#include "r_defs.h"
#include "p_mobj.h"
#include "d_player.h"
#include "p_spec.h"

#include "d_think.h"

void T_MoveFloor (floormove_t* ptr);
void T_PlatRaise (plat_t* ptr);
void T_FireFlicker (fireflicker_t* ptr);
void T_LightFlash (lightflash_t* ptr);
void T_StrobeFlash (strobe_t* ptr);
void T_Glow (glow_t* ptr);
void P_MobjThinker (mobj_t* ptr);
void T_VerticalDoor (vldoor_t* ptr);
void T_MoveCeiling (ceiling_t* ptr);    


void dispatch_thinker_func(int action, void * ptr) {
    switch(action) {
        case F_T_MoveFloor:
            T_MoveFloor ((floormove_t*) ptr); return;
        case F_T_PlatRaise:
            T_PlatRaise ((plat_t*) ptr); return;
        case F_T_FireFlicker:
            T_FireFlicker ((fireflicker_t*) ptr); return;
        case F_T_LightFlash:
            T_LightFlash ((lightflash_t*) ptr); return;
        case F_T_StrobeFlash:
            T_StrobeFlash ((strobe_t*) ptr); return;
        case F_T_Glow:
            T_Glow ((glow_t*) ptr); return;
        case F_P_MobjThinker:
            P_MobjThinker ((mobj_t*) ptr); return;
        case F_T_VerticalDoor:
            T_VerticalDoor ((vldoor_t*) ptr); return;
        case F_T_MoveCeiling: 
            T_MoveCeiling ((ceiling_t*) ptr); return;    
    }
    return;
}

