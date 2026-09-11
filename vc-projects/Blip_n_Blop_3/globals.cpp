/******************************************************************
*
*
*		----------------
*		   Globals.cpp
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

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <vector>
#include <list>
#include <memory>

// #include <ddraw.h>
#include "ben_divers.h"
#include "picture_bank.h"
#include "fonte.h"
#include "super_liste.h"
#include "sound_bank_bb.h"
#include "music_bank.h"
#include "scroll.h"
#include "restore.h"
#include "fond_statique.h"
#include "sprite.h"
#include "giclure.h"
#include "game_state.h"

#include "ben_debug.h"

#define NB_MAX_PLAT	8

//-----------------------------------------------------------------------------
//		Données sur la configuration
//-----------------------------------------------------------------------------

// fps_count/fps_current_count/total_debug moved to debug_stats.cpp
// (DebugStats) - Stage 2 ownership migration.

//-----------------------------------------------------------------------------
//		Surfaces
//-----------------------------------------------------------------------------

SDL::Surface	*	primSurface = NULL;		// Surface primaire
SDL::Surface	*	backSurface = NULL;		// pointeur sur le double buffer supposé
SDL::Surface *	systemSurface = NULL;		// Pour optimiser les accès SYSTEM/SYSTEM
SDL::Surface *	videoA			= NULL;		// cache video

//-----------------------------------------------------------------------------
//		Données scroll et positions
//-----------------------------------------------------------------------------

int			offset;				// offset courant du scroll
int			scr_offset;			// = offset % 640

int			scroll_speed;

// scroll_locked/x_lock/cond_end_lock/flag_end_lock/val_end_lock moved to
// scroll_lock.cpp (ScrollLock) - Stage 2 ownership migration.

bool		no_scroll1;
bool		no_scroll2;

//-----------------------------------------------------------------------------
//		Données sur le niveau
//-----------------------------------------------------------------------------

// scr_level_size/level_size/num_decor/murs_sanglants/y_plat/murs_opaques
// all moved to level.cpp (Level) - Stage 2 ownership migration.

//-----------------------------------------------------------------------------
//		Les listes
//-----------------------------------------------------------------------------

// All 21 entity lists moved to entity_manager.h/.cpp (EntityManager) -
// Stage 2 EntityManager migration, complete.


//-----------------------------------------------------------------------------
//		Données sur les actions à faire
//-----------------------------------------------------------------------------

// phase/slow_phase moved to phase_clock.cpp (PhaseClock) - Stage 2
// ownership migration.

// game_flag[11] moved to game_flags.cpp (GameFlags) - Stage 2 ownership
// migration.

// hold_fire/flag_hold_fire/val_hold_fire moved to hold_fire.cpp (HoldFire).

// rpg_to_play moved to rpg_trigger.cpp (RpgTrigger).

// nb_ennemis_created moved to enemy_stats.cpp (EnemyStats) - Stage 2
// ownership migration.

// intensite_meteo/type_meteo moved to weather.cpp (Weather).

// dy_tremblement/etape_tremblement/amplitude_tremblement/ddy_tremblement and
// tremblement() moved to screen_shake.cpp (ScreenShake) - Stage 2 ownership
// migration.

// okBonus/cowBombOn/okLanceFlame moved to player_toggles.cpp
// (PlayerToggles) - Stage 2 ownership migration.


//-----------------------------------------------------------------------------
//		Les Picture Banks
//-----------------------------------------------------------------------------

// pbk_decor/pbk_blip/pbk_blop/pbk_bb/pbk_misc/pbk_ennemis/pbk_niveau/
// pbk_rpg/pbk_rpg_bb/pbk_inter moved to picture_bank_set.cpp
// (PictureBankSet) - Stage 2 ownership migration.

//-----------------------------------------------------------------------------
//		Les Sounds Banks
//-----------------------------------------------------------------------------

SoundBankBB		sbk_bb;		// Sons BB/divers communs à tous les niveaux
SoundBankBB		sbk_rpg;	// Les musiques des scènes RPG
SoundBankBB		sbk_misc;
SoundBankBB		sbk_niveau;

MusicBank		mbk_niveau;
MusicBank		mbk_inter;
MusicBank		mbk_interl;

char			current_sbk[200];			// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
char			current_sbk_misc[200];		// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
char			current_sbk_niveau[200];	// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
char			current_mbk[200];			// Nom de la MBK courante pour pouvoir la recharger si on enlève puis remet le son
int				current_zik;				// Numéro de la zik jouée

//-----------------------------------------------------------------------------
//		Les Fontes
//-----------------------------------------------------------------------------

// fnt_score_blip/fnt_score_blop/fnt_ammo/fnt_ammo_used/fnt_cool/fnt_rpg/
// fnt_menu/fnt_menus moved to font_bank.cpp (FontBank) - Stage 2
// ownership migration.

//-----------------------------------------------------------------------------
//		Les fonctions cool
//-----------------------------------------------------------------------------


int	plat(int x, int y)
{
	if (x < 0 || x >= g_game_state.level().size() || y >= 480)
		return 0;

	int	tmp;

	for (int i = 0; i < NB_MAX_PLAT; i++) {
		tmp = g_game_state.level().y_plat()[i][x];

		if (y >= tmp && y <= tmp + 10)
			return tmp;
	}
	/*
		if ( mur_opaque( x, y))
			return ( y - (y%8 + 1));
	*/
	return 0;
}

int	plat2(int x, int y)
{
	if (x < 0 || x >= g_game_state.level().size() || y < 0 || y >= 480)
		return -1;

	int	tmp;

	for (int i = 0; i < NB_MAX_PLAT; i++) {
		tmp = g_game_state.level().y_plat()[i][x];

		if (y >= tmp && y <= tmp + 10)
			return i;
	}

	return -1;
}

bool mur_opaque(int x, int y)
{
	if (x < 0 || x >= g_game_state.level().size() || y < 0 || y >= 480)
		return false;

	return g_game_state.level().murs_opaques()[y / 8][x / 8];
}


bool mur_sanglant(int x, int y)
{
	if (x < 0 || x >= g_game_state.level().size() || y < 0 || y >= 480)
		return false;

	return g_game_state.level().murs_sanglants()[y / 8][x / 8];
}

inline void clipedBlit(SDL::Surface * surf, const Picture * pic, int x, int y, Rect * clip)
{
	if (pic == NULL)
		return;

	Rect	r;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		xs = pic->xSize();
	int		ys = pic->ySize();

	x1 = x - pic->xSpot();
	y1 = y - pic->ySpot();

	x2 = x1 + xs;
	y2 = y1 + ys;

	if (x2 < clip->left || x1 > clip->right || y1 > clip->bottom || y2 < clip->top)
		return;

	if (x1 < clip->left) {
		r.left = clip->left - x1;
		x1 = clip->left;
	} else
		r.left = 0;

	if (y1 < clip->top) {
		r.top = clip->top - y1;
		y1 = clip->top;
	} else
		r.top = 0;

	if (x2 > clip->right)
		r.right = xs - (x2 - clip->right);
	else
		r.right = xs;

	if (y2 > clip->bottom)
		r.bottom = ys - (y2 - clip->bottom);
	else
		r.bottom = ys;

	surf->BltFast(x1, y1, pic->Surf(), &r, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
}

bool grave(int x, int y, Picture * pic)
{
	if (pic == NULL || x > (offset + vbuffer_wide - pic->xSize()))
		return false;

	FondStatique	s;
	Sprite *		s2;

	s.x		= x;
	s.y		= y;
	s.pic	= pic;

	s.colFromPic();

        for (auto& s2 : g_game_state.entities().list_fonds_animes()) {
		if (s.collision(s2.get()))
			return false;
	}

	for (auto& s2 : g_game_state.entities().list_plateformes_mobiles()) {
		if (s.collision(s2.get()))
			return false;
	}


	Rect	r;
	int		ni = x / /*640;*/vbuffer_wide;
//	int		no = offset / vbuffer_wide;

	r.top	= 0;
	r.bottom = 480;

	x %= vbuffer_wide;

	if (ni == n_cache - 1) {
		r.left = next_x;
		r.right = vbuffer_wide;

		clipedBlit(videoA, pic, x, y, &r);

		r.left = 0;
		r.right = next_x;

		clipedBlit(videoA, pic, x - vbuffer_wide, y, &r);

		return true;
	} else if (ni == n_cache) {
		r.left = 0;
		r.right = next_x;

		clipedBlit(videoA, pic, x, y, &r);

		r.left = next_x;
		r.right = vbuffer_wide;

		clipedBlit(videoA, pic, x + vbuffer_wide, y, &r);

		return true;
	}

	return false;
}

bool checkRestore()
{
	if (!active) {
		debug << "Blip'n Blop 3 has been desactivated\n";

		while (!active && !app_killed)
			manageMsg();


		for (int i = 0; i < 10; i++)
			manageMsg();

		debug << "Blip'n Blop 3 is active again\n";

		if (primSurface->IsLost()) {
			debug << "Restoring lost surfaces...";

			if (RestoreAll())
				debug << "ok\n";
		}

		return true;
	}

	return false;
}














