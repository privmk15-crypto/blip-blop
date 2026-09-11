/******************************************************************
*
*
*		------------------
*		    Scroll.cpp
*		------------------
*
*
*		Fonctions pour le scroll. Gère le scrolling
*		avec le super buffer qui marche bizarrement sur cette
*		merde de GeForce.
*
*
*		Prosper / LOADED -   V 0.1 - 2 Aout 2000
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"
#include "sprite.h"
#include "globals.h"
#include "game_state.h"
#include "scroll.h"
#include "ben_debug.h"
#include <SDL2/SDL.h>

#include "couille.h"

int vbuffer_wide = WANTED_VBUFFER_WIDE;
int	next_x = 0;
int	xTex = 0;
int	n_img = 0;
int n_cache = 0;

//-----------------------------------------------------------------------------

void drawScrolling()
{
	Rect		r;

	// Pour éviter les mauvaises surprises
	//
	if (offset < 0)
		offset = 0;
	else if (offset > g_game_state.level().size() - SCREEN_W)
		offset = g_game_state.level().size() - SCREEN_W;

	int	x1 = offset % vbuffer_wide;
	int x2 = (offset + SCREEN_W) % vbuffer_wide;	// SCREEN_W: this is the visible-viewport width, not a tile-image width
	int x3 = (offset + vbuffer_wide - 2) % vbuffer_wide;

	r.top	= 0;
	r.bottom = 480;

	

	// 640 below: width of one decor tile image (asset format), not SCREEN_W - do not change
	while (n_img < ((offset + vbuffer_wide - 2) / 640) || (n_img < g_game_state.level().scr_size() && (next_x != ((x3 + 1) % vbuffer_wide)) && (next_x != ((x3) % vbuffer_wide)))) {

		/*static int counter = 0;
		char buf[128];
		sprintf(buf, "test/%d.bmp", counter);
		if (counter >200 && counter<250)
			SDL_SaveBMP(videoA->Get(), buf);
		counter++;*/

		r.left	= xTex;
		r.right = xTex + 2;

		videoA->BltFast(next_x, 0, g_game_state.picture_banks().decor()[g_game_state.level().num_decor()[n_img]]->Surf(), &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

		xTex += 2;

		if (xTex == 640) {	// 640: width of one decor tile image (asset format), not SCREEN_W - do not change
			xTex = 0;
			n_img += 1;
		}

		next_x += 2;

		if (next_x == vbuffer_wide) {
			next_x = 0;
			n_cache += 1;
		}
	}

	if (x1 <= vbuffer_wide - SCREEN_W) {	// SCREEN_W: visible-viewport width
		r.left	= x1;
		r.right = x1 + SCREEN_W;

		backSurface->BltFast(0, 0, videoA, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	} else {
		r.left	= x1;
		r.right = vbuffer_wide;

		backSurface->BltFast(0, 0, videoA, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

		r.left	= 0;
		r.right = x2;

		backSurface->BltFast(vbuffer_wide - x1, 0, videoA, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
}

//-----------------------------------------------------------------------------

void updateScrolling(bool forceOk)
{
	if (g_game_state.scroll_lock().active()) {
		if (offset < g_game_state.scroll_lock().x())
			offset = g_game_state.scroll_lock().x();
	} else if (scroll_speed != 0 && forceOk) {
		offset += scroll_speed;
	} else if (g_game_state.entities().list_joueurs().size() > 0) {
		Sprite *	s;
		int			x_moy = 0;

                for (Couille* s : g_game_state.entities().list_joueurs()) {
			x_moy += s->x;
		}

		x_moy /= g_game_state.entities().list_joueurs().size();
		x_moy -= SCREEN_W / 2;	// Pour centrer

		if (x_moy > offset) {
			if ((x_moy - offset) >= 2)
				offset += 2;
			else
				offset = x_moy;
		}
	}

	if (offset < 0)
		offset = 0;
	else if (offset > g_game_state.level().size() - SCREEN_W)
		offset = g_game_state.level().size() - SCREEN_W;
}
