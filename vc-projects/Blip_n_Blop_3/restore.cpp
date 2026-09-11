#include <cstring>

#include "globals.h"
#include "game_state.h"
#include "config.h"
#include "scroll.h"
#include "ben_debug.h"

bool RestoreAll()
{
	if (primSurface->Restore() != DD_OK) {
		debug << "Cannot restore primary surface.\n";
		return false;
	}

	g_game_state.font_bank().menu().restoreAll();

	// Affiche un "LOADING..."
	//
	g_game_state.font_bank().menu().printC(backSurface, 320, 210, "PLEASE WAIT");
	//primSurface->Flip(NULL, DDFLIP_WAIT);
	graphicInstance->Flip();

	graphicInstance->RestoreAllSurfaces();

	n_img = 0;
	xTex = 0;
	n_cache = 0;
	next_x = 0;

	g_game_state.picture_banks().decor().restoreAll();
	g_game_state.picture_banks().blip().restoreAll();
	g_game_state.picture_banks().blop().restoreAll();
	g_game_state.picture_banks().bb().restoreAll();
	g_game_state.picture_banks().misc().restoreAll();
	g_game_state.picture_banks().ennemis().restoreAll();
	g_game_state.picture_banks().niveau().restoreAll();
	g_game_state.picture_banks().rpg().restoreAll();
	g_game_state.picture_banks().rpg_bb().restoreAll();

	g_game_state.picture_banks().inter().restoreAll();

	g_game_state.font_bank().score_blip().restoreAll();
	g_game_state.font_bank().score_blop().restoreAll();
	g_game_state.font_bank().ammo().restoreAll();
	g_game_state.font_bank().ammo_used().restoreAll();
	g_game_state.font_bank().cool().restoreAll();
	g_game_state.font_bank().rpg().restoreAll();
	g_game_state.font_bank().menus().restoreAll();

	in.reAcquire();

	return true;
}
