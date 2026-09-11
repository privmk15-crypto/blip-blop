
#ifndef _FondVentilo_
#define _FondVentilo_

#include "sprite.h"
#include "game_state.h"
#include "globals.h"

class FondVentilo : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 4;
		}

		pic = g_game_state.picture_banks().niveau()[3 + etape];

		if (x < offset - 100)
			a_detruire = true;
	};
};

#endif
