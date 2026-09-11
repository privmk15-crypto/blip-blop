
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_snorky_base_2.h"
#include "game_state.h"
#include "globals.h"


TirSnorkyBase2::TirSnorkyBase2(int vx, int vy)
{
	dy = vy;
	dx = vx;
	pic = g_game_state.picture_banks().ennemis()[182];
}


void TirSnorkyBase2::update()
{
	x += dx;
	y += dy;

	if (x < offset - 100 || x > offset + SCREEN_W + 60 || y > 520 || y < -50)
		a_detruire = true;

	if (mur_opaque(x , y) != 0)
		a_detruire = true;

	colFromPic();
}
