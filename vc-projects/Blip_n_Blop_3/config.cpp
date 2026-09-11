/******************************************************************
*
*
*		--------------
*		  Config.cpp
*		--------------
*
*		Contient toutes les données sur la config
*		et quelques fonctions pour la gérer.
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#include <stdio.h>
#include "dd_gfx.h"
#include "ben_debug.h"
#include "config.h"
#include "input.h"
#include "control_alias.h"
#include "fmod.h"
#include "globals.h"

bool	vSyncOn = true;

int		mem_flag = DDSURF_BEST;
bool	video_buffer_on = true;
bool	mustFixGforceBug = false;

int		lang_type = LANG_UK;

bool	music_on = true;
bool	sound_on = true;

bool	cheat_on = false;

HiScores	hi_scores;

bool	winSet;
bool fullscreen = false; // THIS IS UGLY AS FUCK. WAY TOO MANY GLOBALS


void load_BB3_config(const char * cfg_file)
{
	FILE *	fic;
	int		a;
	bool	ok = true;

	fic = fopen(cfg_file, "rb");

	if (fic == NULL) {
		debug << "Cannot find config file. Will use default config.\n";
		set_default_config(true);
	} else {
		debug << "Using " << cfg_file << " as configuration file.\n";

		// Fix: none of these fread() calls used to check their return
		// value. A short/truncated/stale config file (e.g. left over
		// from an older build with a different number of fields) would
		// silently leave `a` holding whatever it had from the previous
		// successful read (or uninitialized stack garbage, for the
		// very first field) - setAlias() would then be called with
		// that bogus value for every remaining binding, showing up as
		// "UNDEFINED" in the keys menu (reported as player 1's
		// bindings looking like "unknown"). Now aborts to
		// set_default_config() as soon as any read comes up short,
		// discarding whatever was partially read, instead of
		// proceeding with garbage.
#define READ_OR_BAIL(dst) ok = ok && (fread(&(dst), sizeof(dst), 1, fic) == 1)

		READ_OR_BAIL(vSyncOn);
		READ_OR_BAIL(fullscreen);
		READ_OR_BAIL(lang_type);

		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P1_UP, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P1_DOWN, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P1_LEFT, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P1_RIGHT, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P1_FIRE, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P1_JUMP, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P1_SUPER, a);

		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P2_UP, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P2_DOWN, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P2_LEFT, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P2_RIGHT, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P2_FIRE, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P2_JUMP, a);
		READ_OR_BAIL(a); if (ok) in.setAlias(ALIAS_P2_SUPER, a);

#undef READ_OR_BAIL

		fclose(fic);

		if (!ok) {
			debug << "Config file " << cfg_file
			      << " is short/malformed - using default config "
			         "instead of partially-read garbage.\n";
			set_default_config(true);
		}
	}

	lang_type = LANG_UK;
}

void save_BB3_config(const char * cfg_file)
{
	FILE *	fic;
	int		a;

	fic = fopen(cfg_file, "wb");

	if (fic == NULL) {
		debug << "Cannot save config file.\n";
	} else {
		debug << "Saving " << cfg_file << " as configuration file.\n";


		fwrite(&vSyncOn, sizeof(vSyncOn), 1, fic);
		fwrite(&fullscreen, sizeof(fullscreen), 1, fic);
		fwrite(&lang_type, sizeof(lang_type), 1, fic);

		a = in.getAlias(ALIAS_P1_UP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_DOWN);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_LEFT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_RIGHT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_FIRE);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_JUMP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_SUPER);
		fwrite(&a, sizeof(a), 1, fic);


		a = in.getAlias(ALIAS_P2_UP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_DOWN);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_LEFT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_RIGHT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_FIRE);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_JUMP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_SUPER);
		fwrite(&a, sizeof(a), 1, fic);

		fclose(fic);
	}
}

void set_default_config(bool reset_lang)
{
	if (reset_lang)
		lang_type = LANG_UK;

	in.setAlias(ALIAS_P1_UP, DIK_UP);
	in.setAlias(ALIAS_P1_DOWN, DIK_DOWN);
	in.setAlias(ALIAS_P1_LEFT, DIK_LEFT);
	in.setAlias(ALIAS_P1_RIGHT, DIK_RIGHT);
	in.setAlias(ALIAS_P1_FIRE, DIK_LCONTROL);
	in.setAlias(ALIAS_P1_JUMP, DIK_LMENU);
	in.setAlias(ALIAS_P1_SUPER, DIK_SPACE);

	in.setAlias(ALIAS_P2_UP, DIK_Q);
	in.setAlias(ALIAS_P2_DOWN, DIK_S);
	in.setAlias(ALIAS_P2_LEFT, DIK_D);
	in.setAlias(ALIAS_P2_RIGHT, DIK_F);
	in.setAlias(ALIAS_P2_FIRE, DIK_TAB);
	in.setAlias(ALIAS_P2_JUMP, DIK_G);
	in.setAlias(ALIAS_P2_SUPER, DIK_H);
}
