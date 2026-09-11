
#include "globals.h"
#include "fond_poke_ciel.h"
#include "game_state.h"

FondPokeCiel::FondPokeCiel()
{
	pic = g_game_state.picture_banks().niveau()[48];
}

void FondPokeCiel::update()
{
	etape += 4;
	etape %= 384;

	colFromPic();
}

// Etap 3 (Sprite/Renderer separation) audit finding: bypasses
// Picture/draw() and manipulates SDL::Surface/Rect/BltFast directly
// (clipped scrolling blit at screen edge). Deliberately left
// untouched - flagged in the audit (section C: "niejasne / wymaga
// decyzji") as needing a real design decision before any future
// Renderer extraction, not a mechanical move like the rest of the
// Sprite/Renderer step-1 migration.
void FondPokeCiel::affiche()
{
	Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						decalage = 0;
	int						ys;
	Rect					r;
	int						largeur;

	surf = g_game_state.picture_banks().niveau()[50]->Surf();
	xs = g_game_state.picture_banks().niveau()[50]->xSize();
	ys = g_game_state.picture_banks().niveau()[50]->ySize();

	r.top		= 0;
	r.left		= etape;

	if (x + 192 > offset + 640) {
		largeur = offset + 640 - x;
	}

	else if (x < offset) {
		largeur = 192 ;
		r.left = offset - x + etape;
		decalage = offset - x;
	} else {
		largeur = 192;
	}

	r.right		= etape + largeur;
	r.bottom	= ys;

	/*if ( x+53 > offset+640)
		largeur = offset+640-x;
	else if (x < offset)
	{
		largeur = 53;
		r.left = offset - x;
		decalage = offset - x;
	}
	else
		largeur = 53;*/


	backSurface->BltFast(x - offset + decalage, y + 50, surf, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);


	draw(x, y, g_game_state.picture_banks().niveau()[49]);
}
