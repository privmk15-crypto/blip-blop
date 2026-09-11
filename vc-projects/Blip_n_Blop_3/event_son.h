
#ifndef _EventSon_
#define _EventSon_

#include "event.h"
#include "game_state.h"

class EventSon : public Event
{
public:

	int		nsnd;

	virtual void doEvent()
	{
		g_game_state.sound_banks().sbk_niveau().play(nsnd);
	};

};

#endif