#ifndef _FondDrapeau_
#define _FondDrapeau_

#include "sprite.h"
#include "game_state.h"

class FondDrapeau : public Sprite
{

public:

	virtual void update()
	{
		ss_etape ++;
		ss_etape %= 5;

		if (ss_etape == 0) {
			etape ++;
			etape %= 10;
		}

		pic = g_game_state.picture_banks().niveau()[31 + etape];
	}

};

#endif
