
#ifndef _TirArcCiel_
#define _TirArcCiel

#include "game_state.h"

class TirArcCiel : public Tir
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0)
			etape += 1;

		if (etape >= 15) {
			a_detruire = true;
		} else {
			if (dir == SENS_DROITE)
				pic = g_game_state.picture_banks().ennemis()[48 + etape];
			else
				pic = g_game_state.picture_banks().ennemis()[63 + etape];

			colFromPic();
		}
	};
};

#endif
