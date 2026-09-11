/******************************************************************
*
*
*		------------------
*		  BonusTonneau.h
*		------------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _BonusTonneau_
#define _BonusTonneau_

#include "bonus.h"
#include "game_state.h"

class BonusTonneau : public Bonus
{
public:

	BonusTonneau()
	{
		pic = g_game_state.picture_banks().misc()[47];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		sbk_misc.play(5);

		c->pv = 5;

		Bonus::estPris(c);
	};
};

#endif
