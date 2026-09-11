/******************************************************************
*
*
*		---------------------------
*		    FondAssembleur.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#include "globals.h"
#include "fond_assembleur.h"
#include "game_state.h"

FondAssembleur::FondAssembleur()
{
	//pic = g_game_state.picture_banks().niveau()[53];
}

void FondAssembleur::update()
{
	etape += 1;
	etape %= 432;

	//colFromPic();
}

// Etap 3 (Sprite/Renderer separation) audit finding: bypasses
// Picture/draw() and manipulates SDL::Surface/Rect/BltFast directly
// (clipped blit). Deliberately left untouched - flagged in the audit
// (section C: "niejasne / wymaga decyzji") as needing a real design
// decision before any future Renderer extraction, not a mechanical
// move like the rest of the Sprite/Renderer step-1 migration.
void FondAssembleur::affiche()
{
	//Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						ys;
	Rect					r;
	int						largeur;

	surf = g_game_state.picture_banks().niveau()[53]->Surf();
	xs = g_game_state.picture_banks().niveau()[53]->xSize();
	ys = g_game_state.picture_banks().niveau()[53]->ySize();

	r.top		= etape;
	r.left		= 0;

	if (x + 75 > offset + 640)
		largeur = offset + 640 - x;
	else
		largeur = 75;

	r.right		= largeur;
	r.bottom	= 87 + etape;

	backSurface->BltFast(x - offset, y, surf, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

}
