/******************************************************************
 *
 *		----------------
 *		 GameState.cpp
 *		----------------
 *
 *		See game_state.h for the Stage 2 migration note.
 *
 ******************************************************************/

#include "game_state.h"

GameState g_game_state(g_screen_shake, g_scroll_lock, g_level, g_weather,
                        g_rpg_trigger, g_hold_fire, g_player_toggles);
