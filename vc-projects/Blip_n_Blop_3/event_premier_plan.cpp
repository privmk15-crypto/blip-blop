/******************************************************************
*
*
*		------------------------
*		  EventPremierPlan.cpp
*		------------------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#include "event_premier_plan.h"
#include "game_state.h"
#include "sprite.h"

class PPlan : public Sprite
{
public:
	virtual void update()
	{
	};
};

void EventPremierPlan::doEvent()
{
	PPlan * s = new PPlan();

	s->x = x;
	s->y = y;
	s->pic = g_game_state.picture_banks().niveau()[id_fond];

	g_game_state.entities().list_premiers_plans().emplace_back(s);

}
