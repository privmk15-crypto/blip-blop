
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_debouche_chiote.h"
#include "game_state.h"
#include "globals.h"
//#include "bendebug.h"

TirDebouchechiote::TirDebouchechiote(int n_pbk_ennemis, int vx, int vy)
{
	pic = g_game_state.picture_banks().ennemis()[n_pbk_ennemis];
	dy = vy;
	dx = vx;
}


void TirDebouchechiote::update()
{
	x += dx;
	y += dy;

	if (x < offset - 100 || x > offset + SCREEN_W + 60 || y > 520 || y < -50)
		a_detruire = true;

	colFromPic();
}
