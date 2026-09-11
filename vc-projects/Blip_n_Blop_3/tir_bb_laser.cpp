/******************************************************************
*
*
*		-----------------
*		  TirBBLaser.cpp
*		-----------------
*
*		Pour les tirs de laser de Blip/Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_bb_laser.h"
#include "ben_debug.h"
#include "game_state.h"
#include "globals.h"

TirBBLaser::TirBBLaser() : base(0), hauteur(0), largeur(0)
{
}

void TirBBLaser::setDir(int d)
{
	TirBB::setDir(d);

	base = hauteur = largeur = 0;

	dir /= 2;


	int nx = x;
	int ny = y;

	switch (dir) {
		case 0:		// Bas

			if (y < 0) {
				ny = y = 0;
			}

			while (ny > -5 && ny < 485 && !mur_opaque(nx, ny))
				ny += 8;

			hauteur = ny - y;
			base = 140;

			x1 = x;
			y1 = y;
			x2 = x + 6;
			y2 = ny;
			col_on = true;
			break;

		case 2:		// Droite

			while (nx > offset - 5 && nx < offset + SCREEN_W + 5 && !mur_opaque(nx, ny))
				nx += 8;

			largeur = nx - x;
			base = 136;

			x1 = x;
			y1 = y;
			x2 = nx;
			y2 = y + 6;
			col_on = true;
			break;

		case 4:		// Haut

			while (ny > -5 && ny < 485 && !mur_opaque(nx, ny))
				ny -= 8;

			hauteur = y - ny;
			base = 140;

			x1 = x;
			y1 = ny;
			x2 = x + 6;
			y2 = y;
			y = ny;
			col_on = true;
			break;

		case 6:		// Gauche

			while (nx > offset - 5 && nx < offset + SCREEN_W + 5 && !mur_opaque(nx, ny))
				nx -= 8;

			largeur = x - nx;
			base = 136;

			x1 = nx;
			y1 = y;
			x2 = x;
			y2 = y + 6;
			x = nx;
			col_on = true;
			break;
	}

	ss_etape = 2;
}

void TirBBLaser::update()
{
	ss_etape -= 1;

	if (ss_etape == 0)
		a_detruire = true;
}


// Etap 3 (Sprite/Renderer separation) audit finding: the hardest of
// the 5 flagged cases - bypasses Picture/draw() with direct
// SDL::Surface/Rect/BltFast calls AND queries mur_opaque() (level
// collision geometry) inside the render loop to determine how far to
// draw the laser beam, i.e. this affiche() does real gameplay-adjacent
// computation, not just conditional drawing. Read-only (no state
// mutation found), but deliberately left untouched - flagged in the
// audit (section C) as needing a real design decision (e.g. moving
// the raycast into update(), storing a beam-length field, and letting
// affiche() only draw it) before any future Renderer extraction.
void TirBBLaser::affiche(RenderQueue& rq)
{
	SDL::Surface *	surf = g_game_state.picture_banks().bb()[base + etape]->Surf();
	Rect	r;
	int		xx = x - offset;
	int		nx = x;
	int		ny = y;

	switch (dir) {
		case 0:				// Bas ----------------------------------
			r.top	 = 0;
			r.left	 = 0;
			r.right	 = 6;


			if (y + hauteur > 479)
				hauteur = 479 - y;

			r.bottom = hauteur;


			backSurface->BltFast(xx, y, surf, &r, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
			if (y + hauteur < 480)
				draw(x + 2, y + hauteur, g_game_state.picture_banks().misc()[74 + etape]);
			break;

		case 1:				// Bas/droite ---------------------------

			while (nx > offset - 20 && nx < offset + SCREEN_W + 20 &&
			        ny > -50 && ny < 500 && !mur_opaque(nx, ny)) {
				draw(nx, ny, g_game_state.picture_banks().bb()[144 + etape]);
				nx += 8;
				ny += 8;
			}

			draw(nx, ny + 5, g_game_state.picture_banks().misc()[74 + etape]);
			break;

		case 2:				// Droite -------------------------------
			r.top    = 0;
			r.left	 = 0;
			r.bottom = 6;

			if (xx + largeur > SCREEN_W)
				r.right = SCREEN_W - xx;
			else
				r.right = largeur;

			backSurface->BltFast(xx, y, surf, &r, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

			if (xx + largeur < SCREEN_W)
				draw(x + largeur, y + 3, g_game_state.picture_banks().misc()[74 + etape]);
			break;

		case 3:				// Haut/droite --------------------------

			while (nx > offset - 20 && nx < offset + SCREEN_W + 20 &&
			        ny > -20 && ny < 500 && !mur_opaque(nx, ny)) {
				draw(nx, ny, g_game_state.picture_banks().bb()[148 + etape]);
				nx += 8;
				ny -= 8;
			}

			draw(nx - 5, ny + 10, g_game_state.picture_banks().misc()[74 + etape]);
			break;

		case 4:				// Haut ---------------------------------
			r.top	 = 0;
			r.left	 = 0;
			r.right	 = 6;

			if (y < 0) {
				hauteur += y;
				y = 0;
			}

			r.bottom = hauteur;

			backSurface->BltFast(xx, y, surf, &r, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

			if (y > 0)
				draw(x + 3, y, g_game_state.picture_banks().misc()[74 + etape]);
			break;

		case 5:				// Haut/gauche --------------------------

			while (nx > offset - 20 && nx < offset + SCREEN_W + 20 &&
			        ny > -20 && ny < 500 && !mur_opaque(nx, ny)) {
				draw(nx, ny, g_game_state.picture_banks().bb()[144 + etape]);
				nx -= 8;
				ny -= 8;
			}

			draw(nx + 5, ny + 10, g_game_state.picture_banks().misc()[74 + etape]);
			break;

		case 6:				// Gauche --------------------------------
			r.top    = 0;
			r.left	 = 0;
			r.bottom = 6;

			if (xx < 0) {
				r.right = largeur - xx;
				xx = 0;
			} else
				r.right  = largeur;

			backSurface->BltFast(xx, y, surf, &r, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

			if (xx > 0)
				draw(x + 2, y + 3, g_game_state.picture_banks().misc()[74 + etape]);
			break;

		case 7:				// Bas/gauche ---------------------------

			while (nx > offset - 20 && nx < offset + SCREEN_W + 20 &&
			        ny > -50 && ny < 500 && !mur_opaque(nx, ny)) {
				draw(nx, ny, g_game_state.picture_banks().bb()[148 + etape]);
				nx -= 8;
				ny += 8;
			}

			draw(nx, ny + 5, g_game_state.picture_banks().misc()[74 + etape]);
			break;

	}
}


bool TirBBLaser::collision(const Sprite * s) const
{
	switch (dir) {
		case 0:
		case 2:
		case 4:
		case 6:
			return Sprite::collision(s);
			break;
	}

	int	y_laser1;
	int	y_laser2;

	int xe1 = s->x1;
	int xe2 = s->x2;
	int ye1 = s->y1;
	int ye2 = s->y2;

	if (s->col_on == false)
		return false;

	switch (dir) {
		case 1: // Bas droite
			if (xe2 < x || ye2 < y)
				return false;

			y_laser1 = (xe1 - x) + y;
			y_laser2 = (xe2 - x) + y;

			break;

		case 3:	// Haut droite
			if (xe2 < x || ye1 > y)
				return false;

			y_laser1 = -(xe1 - x) + y;
			y_laser2 = -(xe2 - x) + y;

			break;

		case 5: // Haut gauche
			if (xe1 > x || ye1 > y)
				return false;

			y_laser1 = (xe1 - x) + y;
			y_laser2 = (xe2 - x) + y;

			break;

		case 7: // Bas gauche
			if (xe1 > x || ye2 < y)
				return false;

			y_laser1 = -(xe1 - x) + y;
			y_laser2 = -(xe2 - x) + y;

			break;
	}

	return ((y_laser1 > ye1 && y_laser1 < ye2) || (y_laser2 > ye1 && y_laser2 < ye2));
}


