/******************************************************************
*
*
*		-------------------
*		  EventHoldFire.h
*		-------------------
*
*		Classe Evenement Hold Fire
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventHoldFire_
#define _EventHoldFire_

#include "event.h"
#include "game_state.h"

class EventHoldFire : public Event
{
public:

	int		flag;
	int		val;

	virtual void doEvent()
	{
		g_game_state.hold_fire().Engage(flag, val);
	};
};

#endif