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
#include "hold_fire.h"

class EventHoldFire : public Event
{
public:

	int		flag;
	int		val;

	virtual void doEvent()
	{
		g_hold_fire.Engage(flag, val);
	};
};

#endif