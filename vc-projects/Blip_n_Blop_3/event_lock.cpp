/******************************************************************
*
*
*		---------------
*		  EventLock.h
*		---------------
*
*		Classe Evenement Lock
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#include "event_lock.h"
#include "scroll_lock.h"
#include "ben_debug.h"

void EventLock::doEvent()
{
	g_scroll_lock.Engage(x_activation, cond, flag, val);
}
