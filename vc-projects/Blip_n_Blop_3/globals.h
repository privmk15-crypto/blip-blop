/******************************************************************
*
*
*		----------------
*		   Globals.h
*		----------------
*
*		Liste de tous les trucs globaux et donc accessibles
*		pour TOUT LE MONDE.
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#pragma once

#include <list>

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

// #include <ddraw.h>
#include "ben_debug.h"
// control_p1.h/control_p2.h are no longer needed for ctrlP1/ctrlP2 (moved to
// Game, Stage 2) but are kept here anyway: several files (character_selection
// .cpp, restore.cpp, rpg_player.cpp, ...) reach `in` (input.h) and
// DIK_*/ALIAS_* (control_alias.h) only transitively through this chain,
// without including either header themselves. Confirmed by a real CI
// failure when these were removed - do not remove again without first
// auditing every file that includes globals.h for direct use of `in`/
// DIK_*/ALIAS_*.
#include "control_p1.h"
#include "control_p2.h"
#include "picture_bank.h"  // kept: PictureBank type used elsewhere via transitive include
#include "fonte.h"  // kept: Fonte type still used by game.cpp's fnt_p1/fnt_p2 pointers
#include "super_liste.h"
#include "sound_bank_bb.h"  // kept: transitive-include safety, see fonte.h/picture_bank.h above
#include "music_bank.h"  // kept: transitive-include safety, see fonte.h/picture_bank.h above

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define LATENCE_GRAVITE		7
#define GRAVITE_MAX			4

#define	NB_MAX_PLAT			8

#define METEO_PLUIE			0
#define METEO_NEIGE			1
#define METEO_DEFORME		2

#define FLAG_USER0			0
#define FLAG_USER1			1
#define FLAG_USER2			2
#define FLAG_USER3			3

#define FLAG_BULLES			4
#define FLAG_BONUS			5
#define FLAG_TIMER			6
#define FLAG_GEN_OFF		7
#define FLAG_NB_KILL		8
#define FLAG_NB_ENN			9
#define FLAG_NB_GEN			10

//-----------------------------------------------------------------------------
//		Données sur la configuration
//-----------------------------------------------------------------------------

// fps_count/fps_current_count/total_debug moved into DebugStats
// (debug_stats.h) as part of the Stage 2 ownership migration.

//-----------------------------------------------------------------------------
//		Surfaces
//-----------------------------------------------------------------------------

extern SDL::Surface	*	primSurface;	// Surface primaire
extern SDL::Surface	*	backSurface;	// pointeur sur le double buffer supposé
extern SDL::Surface  *	systemSurface;	// Pour optimiser les accès SYSTEM/SYSTEM
extern SDL::Surface  *	videoA;			// cache video

//-----------------------------------------------------------------------------
//		Données scroll et positions
//-----------------------------------------------------------------------------


extern int			offset;				// offset courant du scroll
extern int			scr_offset;			// = offset % 640

// Etap 4 (Full HD prep, step 2): single named constant for the width of
// the visible screen/camera viewport (backSurface is still 640x480 -
// see picture.h's XPIC_MAX/YPIC_MAX, untouched at this step). Replaces
// scattered literal 640 at "is this actor past the right/left edge of
// the visible screen" call sites (enemy/shot AI turnaround checks,
// fond_* edge clipping, the camera clamp in scroll.cpp/game.cpp).
// Deliberately NOT used yet for: XPIC_MAX/YPIC_MAX (picture.h),
// CreatePrimary()/backSurface/win_size (graphics.cpp/blip_n_blop_3.cpp,
// reserved for a later step), vbuffer_wide's 840-wide scroll cache
// buffer (scroll.cpp - a different, already-named concept, mixed with
// literal 640 in ways that need separate, careful review), or any of
// cine_player/rpg_player/character_selection/screen_shake/menus/HUD
// (not yet audited for this constant).
constexpr int		SCREEN_W = 640;

extern int			scroll_speed;

// scroll_locked/x_lock/cond_end_lock/flag_end_lock/val_end_lock moved into
// ScrollLock (scroll_lock.h) as part of the Stage 2 ownership migration.

extern bool			no_scroll1;			// Pour arrêter le scroll quand
extern bool			no_scroll2;			// blip ou blop meure

// okBonus/cowBombOn/okLanceFlame moved into PlayerToggles
// (player_toggles.h) as part of the Stage 2 ownership migration.

//-----------------------------------------------------------------------------
//		Données sur le niveau
//-----------------------------------------------------------------------------

// scr_level_size/level_size/num_decor/murs_sanglants/y_plat/murs_opaques
// all moved into Level (level.h) as part of the Stage 2 ownership
// migration.


//-----------------------------------------------------------------------------
//		Les listes
//-----------------------------------------------------------------------------

// All 21 entity lists (list_joueurs, list_tirs_bb, list_cow, list_impacts,
// list_vehicules, list_event_endormis, list_event, list_gen_ennemis,
// list_gen_bonus, list_meteo, list_bulles, list_ennemis,
// list_tirs_ennemis, list_bonus, list_fonds_animes, list_fonds_statiques,
// list_premiers_plans, list_plateformes_mobiles, list_txt_cool,
// list_giclures, list_gore) moved into EntityManager (entity_manager.h)
// as part of the Stage 2 EntityManager migration.


//-----------------------------------------------------------------------------
//		Données sur les actions à faire
//-----------------------------------------------------------------------------

// phase/slow_phase moved into PhaseClock (phase_clock.h) as part of the
// Stage 2 ownership migration.

// game_flag[11] moved into GameFlags (game_flags.h) as part of the
// Stage 2 ownership migration.

// hold_fire/flag_hold_fire/val_hold_fire moved into HoldFire (hold_fire.h)
// as part of the Stage 2 ownership migration.

// rpg_to_play moved into RpgTrigger (rpg_trigger.h).

// nb_ennemis_created moved into EnemyStats (enemy_stats.h) as part of the
// Stage 2 ownership migration.

// intensite_meteo/type_meteo moved into Weather (weather.h).

// dy_tremblement/etape_tremblement/amplitude_tremblement/ddy_tremblement
// moved into ScreenShake (screen_shake.h) as part of the Stage 2 ownership
// migration. tremblement() below still forwards to it, unchanged.

//-----------------------------------------------------------------------------
//		Les Picture Banks
//-----------------------------------------------------------------------------

// pbk_decor/pbk_blip/pbk_blop/pbk_bb/pbk_misc/pbk_ennemis/pbk_niveau/
// pbk_rpg/pbk_rpg_bb/pbk_inter moved into PictureBankSet
// (picture_bank_set.h) as part of the Stage 2 ownership migration.

//-----------------------------------------------------------------------------
//		Les Sounds Banks
//-----------------------------------------------------------------------------

// sbk_bb/sbk_rpg/sbk_misc/sbk_niveau/mbk_niveau/mbk_inter/mbk_interl/
// current_sbk/current_sbk_misc/current_sbk_niveau/current_mbk/current_zik
// moved into SoundBankSet (sound_bank_set.h) as part of the Stage 2
// ownership migration.

//-----------------------------------------------------------------------------
//		Les Fontes
//-----------------------------------------------------------------------------

// fnt_score_blip/fnt_score_blop/fnt_ammo/fnt_ammo_used/fnt_cool/fnt_rpg/
// fnt_menu/fnt_menus moved into FontBank (font_bank.h) as part of the
// Stage 2 ownership migration.

//-----------------------------------------------------------------------------
//		Les fonctions cool
//-----------------------------------------------------------------------------

int		plat(int x, int y);	// Retourne l'ordonnée de la plateforme (0 si pas de plat)
int		plat2(int x, int y);
bool	mur_opaque(int x, int y);
bool	mur_sanglant(int x, int y);
bool	grave(int x, int y, Picture * pic);
void	tremblement(int amp);
bool	checkRestore();


inline void draw(int x, int y, const Picture * pic)
{
	if (pic != NULL)
		pic->BlitTo(backSurface, x - offset, y);
}
