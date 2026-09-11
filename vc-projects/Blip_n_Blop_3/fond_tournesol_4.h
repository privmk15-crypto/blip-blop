#ifndef _FondTournesol4_
#define _FondTournesol4_

#include "sprite.h"
#include "game_state.h"

class FondTournesol4 : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 10;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 2;
		}

		pic = g_game_state.picture_banks().niveau()[26 + etape];
	};
};

#endif
