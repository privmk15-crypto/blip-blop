/******************************************************************
*
*
*		-------------------
*		    Giclure.cpp
*		-------------------
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#include "giclure.h"
#include "game_state.h"

void Giclure::update()
{
	if (pere->a_detruire || pere->etat == ETAT_MEURE) {
		a_detruire = true;
		return;
	}

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 4)
		a_detruire = true;
	else
		pic = g_game_state.picture_banks().misc()[15 + dir * 4 + etape];

	x = pere->x + deltax;
	y = pere->y + deltay;
}

