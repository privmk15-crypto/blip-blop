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
#include "fonte.h"
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

extern int			fps_count;
extern int			fps_current_count;

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

extern bool			okBonus;
extern bool			cowBombOn;
extern bool			okLanceFlame;

//-----------------------------------------------------------------------------
//		Données sur le niveau
//-----------------------------------------------------------------------------

// scr_level_size/level_size/num_decor/murs_sanglants moved into Level
// (level.h) as part of the Stage 2 ownership migration. y_plat/murs_opaques
// stay here deliberately - see level.h for why.

extern int	**		y_plat;				// Plateformes (ordonnées)

extern bool **		murs_opaques;		// Murs opaques (=true)


//-----------------------------------------------------------------------------
//		Les listes
//-----------------------------------------------------------------------------

// FIXME: They're all lists instead of ideally vectors because we sometimes
// append during iterations and relocating is then STRICTLY forbidden
class Couille;
extern std::vector<Couille*> list_joueurs; // FIXME: make it owning?
class TirBB;
extern std::list<TirBB*> list_tirs_bb;
class TirBBVache;
extern std::list<std::unique_ptr<TirBBVache>> list_cow;
class Explosion;
// FIXME: should be owning by value but can't, because of circular deps
extern std::list<std::unique_ptr<Explosion>> list_impacts; 

class Vehicule;
extern std::list<std::unique_ptr<Vehicule>> list_vehicules;

class Event;
extern std::list<std::unique_ptr<Event>> list_event_endormis;
extern std::list<std::unique_ptr<Event>> list_event;

class Ennemi;
extern std::list<std::unique_ptr<Ennemi>> list_ennemis;
class Tir;
extern std::list<std::unique_ptr<Tir>> list_tirs_ennemis;
class GenEnnemi;
extern std::list<std::unique_ptr<GenEnnemi>> list_gen_ennemis;

class Bonus;
extern std::list<std::unique_ptr<Bonus>> list_bonus;
class GenBonus;
extern std::list<std::unique_ptr<GenBonus>> list_gen_bonus;

class Sprite;
extern std::list<std::unique_ptr<Sprite>> list_fonds_animes;
extern std::list<std::unique_ptr<Sprite>> list_fonds_statiques;
extern std::list<std::unique_ptr<Sprite>> list_premiers_plans;
extern std::list<std::unique_ptr<Sprite>> list_plateformes_mobiles;

class TexteCool;
extern std::list<std::unique_ptr<TexteCool>> list_txt_cool;

// FIXME: should prolly be a list of Giclure, but GoreGiclure doesn't inherit
// Giclure
extern std::list<std::unique_ptr<Sprite>> list_giclures;
// FIXME all things put insite list_gore don't have a common base aside from
// Sprite
extern std::list<std::unique_ptr<Sprite>> list_gore;

extern std::list<Sprite*> list_meteo;
class Bulle;
extern std::list<std::unique_ptr<Bulle>> list_bulles;


//-----------------------------------------------------------------------------
//		Données sur les actions à faire
//-----------------------------------------------------------------------------

extern bool			phase;				// Pour les clignotements
extern bool			slow_phase;

extern int			game_flag[11];

// hold_fire/flag_hold_fire/val_hold_fire moved into HoldFire (hold_fire.h)
// as part of the Stage 2 ownership migration.

// rpg_to_play moved into RpgTrigger (rpg_trigger.h).

extern int			nb_ennemis_created;

// intensite_meteo/type_meteo moved into Weather (weather.h).

// dy_tremblement/etape_tremblement/amplitude_tremblement/ddy_tremblement
// moved into ScreenShake (screen_shake.h) as part of the Stage 2 ownership
// migration. tremblement() below still forwards to it, unchanged.

extern bool			total_debug;

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

extern Fonte			fnt_score_blip;
extern Fonte			fnt_score_blop;
extern Fonte			fnt_ammo;
extern Fonte			fnt_ammo_used;
extern Fonte			fnt_cool;
extern Fonte			fnt_rpg;
extern Fonte			fnt_menu;
extern Fonte			fnt_menus;

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
