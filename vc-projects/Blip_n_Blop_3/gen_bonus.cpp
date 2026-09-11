/******************************************************************
*
*
*		-----------------
*		  GenBonus.cpp
*		-----------------
*
*
*
*		Prosper / LOADED -   5 Aout 2000
*
*
*
******************************************************************/

#include <cstdlib>
#include "globals.h"
#include "game_state.h"
#include "gen_bonus.h"
#include "make_bonus.h"

GenBonus::GenBonus() : t(0), a_detruire(false)
{
}

void GenBonus::update()
{
	if (g_game_state.entities().list_bonus().size() < 3) {
		t += 1;
		t %= periode;

		if (t == 0) {
			MakeBonus(offset + SCREEN_W / 2 - 200 + rand() % 400, -50);
		}

		if (offset > x + 500)
			a_detruire = true;
	}
}


