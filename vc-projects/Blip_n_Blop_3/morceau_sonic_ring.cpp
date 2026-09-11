
/******************************************************************
*
*
*		-----------------------
*		   MorceauSonicRing.cpp
*		-----------------------
*
*		Ring de Sonic qui Giclent...
*
*		Mephisto / LOADED -   V 0.1 - 20 Decembre 2000
*
*
*
******************************************************************/

#include "morceau_sonic_ring.h"
#include "game_state.h"
#include "globals.h"

//implementation de la classe MorceauSonicRing

MorceauSonicRing::MorceauSonicRing(int vx, int vy): dx(vx)
{
	dy  = vy;
}

void MorceauSonicRing::update()
{
	x += dx;
	tombe2();

	if (plat(x + dx, y + dy) != 0) {
		if (dy > 2) {
			dy = -dy + 1;
		} else if ((dy == 2) || (dy == 1)) {
			dy = -2;
		}
	}

	ss_etape ++;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape ++;
		etape %= 4;
	}

	pic = g_game_state.picture_banks().ennemis()[119 + etape];
	updateADetruire();
}
