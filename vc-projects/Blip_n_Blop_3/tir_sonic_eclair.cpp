
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_sonic_eclair.h"
#include "game_state.h"

TirSoniceclair::TirSoniceclair()
{
	ss_etape = 0;
	etape = 0;
}


void TirSoniceclair::update()
{
	ss_etape += 1;
	ss_etape %= 3;


	if (ss_etape == 0) {
		etape += 1;
	}
	pic = g_game_state.picture_banks().ennemis()[56 + ss_etape];

	if (etape > 30) {
		colFromPic();
		if (etape > 36) {
			a_detruire = true;
		}
	}
	if (etape == 0 || etape > 30) {
		tremblement(7);
	}

}

void TirSoniceclair::affiche()
{
	if (etape == 0 || etape > 30) {
		Sprite::affiche();
	}
}
