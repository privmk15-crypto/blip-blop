/******************************************************************
*
*
*		---------------
*		  BonusVache.h
*		---------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _BonusVache_
#define _BonusVache_

#include "bonus.h"
#include "game_state.h"

class BonusVache : public Bonus
{
public:

	BonusVache()
	{
		pic = g_game_state.picture_banks().misc()[48];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		sbk_misc.play(1);

		c->nb_cow_bomb += 1;

		Bonus::estPris(c);
	};
};

#endif
