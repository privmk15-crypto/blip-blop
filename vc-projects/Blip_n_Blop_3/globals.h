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
#include "picture_bank.h"
#include "fonte.h"  // kept: Fonte type still used by game.cpp's fnt_p1/fnt_p2 pointers
#include "super_liste.h"
#include "sound_bank_bb.h"
#include "music_bank.h"

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

extern int			game_flag[11];

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

extern PictureBank		pbk_decor;	// pbk des décors
extern PictureBank		pbk_blip;	// pbk de blip
extern PictureBank		pbk_blop;
extern PictureBank		pbk_bb;		// pbk commune à blip et blop
extern PictureBank		pbk_misc;	// pbk "diverse"
extern PictureBank		pbk_ennemis;// pbk des ennemis
extern PictureBank		pbk_niveau;	// pbk du niveau (fonds animes & co)
extern PictureBank		pbk_rpg;	// Gueules des RPGs du niveau
extern PictureBank		pbk_rpg_bb; // Les gueules de Blip et Blop
extern PictureBank		pbk_inter;	// L'interface

//-----------------------------------------------------------------------------
//		Les Sounds Banks
//-----------------------------------------------------------------------------

extern SoundBankBB		sbk_bb;		// Sons BB/divers communs à tous les niveaux
extern SoundBankBB		sbk_rpg;	// Les musiques des scènes RPG
extern SoundBankBB		sbk_misc;
extern SoundBankBB		sbk_niveau;

extern MusicBank		mbk_niveau;
extern MusicBank		mbk_inter;
extern MusicBank		mbk_interl;

extern char				current_sbk[];			// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
extern char				current_sbk_misc[];		// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
extern char				current_sbk_niveau[];	// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
extern char				current_mbk[];			// Nom de la MBK courante pour pouvoir la recharger si on enlève puis remet le son
extern int				current_zik;			// Numéro de la zik jouée

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
