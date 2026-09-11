//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_cadeau.h"
#include "game_state.h"
#include "globals.h"

TirCadeau::TirCadeau()
{
	pic = g_game_state.picture_banks().ennemis()[56] ;
	noCol() ;
}

void TirCadeau::update()
{
	if (!mur_opaque(x, y))
		tombe() ;

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0) {
		etape += 1;

		if (etape == 20) {
			g_game_state.sound_banks().sbk_misc().play(11);
		}
	}

	if (etape >= 20) {
		col_on = true ;
		pic = g_game_state.picture_banks().ennemis()[80 + etape] ;
	}

	if (etape > 35)
		a_detruire = true ;

	colFromPic();

	if (etape >= 30)
		noCol() ;
}
