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
#include "game_state.h"
#include "ben_debug.h"

void EventLock::doEvent()
{
	g_game_state.scroll_lock().Engage(x_activation, cond, flag, val);
}
