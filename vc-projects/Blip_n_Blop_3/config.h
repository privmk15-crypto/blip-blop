/******************************************************************
*
*
*		------------
*		  Config.h
*		------------
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

#ifndef _Config_
#define _Config_

#include "hi_scores.h"

extern bool		vSyncOn;
extern bool		fullscreen;

extern int		mem_flag;
extern bool		video_buffer_on;
extern bool		mustFixGforceBug;

#define LANG_FR		0
#define LANG_UK		1

extern int		lang_type;

extern bool		music_on;
extern bool		sound_on;

// 0-255, matching FMOD's own volume convention (FSOUND_SetSFXMasterVolume,
// FMUSIC_SetMasterVolume). Applied via apply_volume_settings() below.
extern int		music_volume;
extern int		sfx_volume;

// Pushes music_volume/sfx_volume to FMOD (FSOUND_SetSFXMasterVolume for
// sound effects, MusicBank::setVol() for each music bank) and, for
// music, is also what MusicBank::open() itself calls on every newly
// loaded track - so call this once after changing either value (the
// options menu does), not after every level load.
void apply_volume_settings();

extern bool		cheat_on;

extern HiScores	hi_scores;

extern bool		winSet;

void load_BB3_config(const char * cfg_file);
void save_BB3_config(const char * cfg_file);
void set_default_config(bool reset_lang = false);

#endif
