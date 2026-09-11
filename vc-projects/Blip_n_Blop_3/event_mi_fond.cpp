
#include "globals.h"
#include "game_state.h"
#include "event_mi_fond.h"
#include "fond_statique.h"

void EventMiFond::doEvent()
{
	Sprite * s = new FondStatique();

	s->x = x;
	s->y = y;
	s->pic = pbk_niveau[id];

	g_game_state.entities().list_fonds_statiques().emplace_back(s);
}
