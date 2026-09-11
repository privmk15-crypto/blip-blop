/******************************************************************
*
*
*		---------------------------
*		    FondBossventilo.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 18 Janvier 2001
*
*
*
******************************************************************/


#include "fond_bossventilo.h"
#include "game_state.h"


void FondBossventilo::update()
{
	ss_etape ++;
	ss_etape %= 3;
	if (ss_etape == 0) {
		etape ++;
		etape %= 4;
	}

	pic = g_game_state.picture_banks().niveau()[60 + etape];
	updateADetruire();
}
