
#include "event_music.h"
#include "globals.h"
#include "game_state.h"

void EventMusic::doEvent()
{
	if (play) {
		if (g_game_state.sound_banks().current_zik() != -1)
			g_game_state.sound_banks().mbk_niveau().stop(g_game_state.sound_banks().current_zik());

		g_game_state.sound_banks().mbk_niveau().play(id);
		g_game_state.sound_banks().current_zik() = id;
	} else {
		g_game_state.sound_banks().mbk_niveau().stop(id);
		g_game_state.sound_banks().current_zik() = -1;
	}
}
