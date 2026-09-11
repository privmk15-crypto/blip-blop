/******************************************************************
*
*
*		---------------------------
*		    FondCube.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"
#include "fond_cube.h"
#include "game_state.h"

int FondCube::etape_synchro = 0;
bool FondCube::synchro = false;
int FondCube::ss_etape_synchro = 0;

void FondCube::update()
{
	if (g_game_state.phase_clock().phase() != synchro) {
		synchro = g_game_state.phase_clock().phase();

		ss_etape_synchro += 1;
		ss_etape_synchro %= 5;

		if (ss_etape_synchro == 0) {
			etape_synchro += 1;
			etape_synchro %= 9;
		}
	}

	pic = pbk_niveau[etape_synchro];

	if (x < offset - 100)
		a_detruire = true;
};
