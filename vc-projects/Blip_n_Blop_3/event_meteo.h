/******************************************************************
*
*
*		-------------------
*		  EventMeteo.h
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

#ifndef _EventMeteo_
#define _EventMeteo_

#include "event.h"
#include "ben_debug.h"
#include "game_state.h"

class EventMeteo : public Event
{
public:

	int		intensite;
	int		type;

	virtual void doEvent()
	{
		g_game_state.weather().Set(intensite, type);
	};
};

#endif
