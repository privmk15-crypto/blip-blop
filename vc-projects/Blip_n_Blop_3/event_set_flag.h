/******************************************************************
*
*
*		-------------------
*		  EventSetFlag.h
*		-------------------
*
*		Classe Evenement Set Flag
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventSetFlag_
#define _EventSetFlag_

#include "event.h"
#include "game_state.h"

class EventSetFlag : public Event
{
public:

	int		flag;
	int		val;

	virtual void doEvent()
	{
		g_game_state.game_flags()[flag] = val;
	};
};

#endif