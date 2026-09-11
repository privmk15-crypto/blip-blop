
#ifndef _FondWindows_
#define _FondWindows_

#include "sprite.h"
#include "game_state.h"

class FondWindows : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 180;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 4;
		}

		int i = 54;

		switch (etape) {
			case 1:
			case 2:
				i = 56;
				break;
			case 3:
				i = 57;
				break;
		}

		pic = g_game_state.picture_banks().niveau()[i];

		updateADetruire();
	};

};

#endif
