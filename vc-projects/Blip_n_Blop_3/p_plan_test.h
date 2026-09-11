
#ifndef _PPlanTest_
#define _PPlanTest_

#include "sprite.h"
#include "game_state.h"
#include "globals.h"

class PPlanTest : public Sprite
{
public:
	PPlanTest()
	{
		pic = g_game_state.picture_banks().niveau()[2];
	};

	virtual void update()
	{
		if (x < offset - 300)
			a_detruire = true;
	};
};

#endif
