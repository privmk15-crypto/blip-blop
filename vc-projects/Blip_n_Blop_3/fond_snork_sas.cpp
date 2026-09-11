/******************************************************************
*
*
*		-----------------------
*		    FondSnorkSas.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 18 Janvier 2001
*
*
*
******************************************************************/


#include "globals.h"
#include "game_state.h"
#include "fond_snork_sas.h"
#include "enemy.h"

int FondSnorkSas1::etat = 0; // 0 pour etat du sas 1 ouvert , 1 pour fermé

FondSnorkSas1::FondSnorkSas1(): nb_joueur(0)
{
	etape = 0;
	//pic = g_game_state.picture_banks().niveau()[53];
}

void FondSnorkSas1::update()
{
	if (!etat) { // si le sas n'est pas fermé..
		if ((tete_turc != NULL) && (tete_turc->x > 1400)) {
			nb_joueur ++;
			if (etape < 222) {
				if (nb_joueur >= 2) {
					etape += 2;
				}
				/*
				else
					il y en a peut etre un autre sous la porte..
				*/
			} else {
				etat = 1; // Sas 1 fermé...
			}
		} else {
			nb_joueur = 0;
		}




		if (etape % 8 == 0) {
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 8) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 16) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 24) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 32) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 40) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 48) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 56) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 64) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 72) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 80) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 88) / 8] = true;
			g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 96) / 8] = true;

		}
	}
}

// Etap 3 (Sprite/Renderer separation) audit finding: FondSnorkSas1/2's
// affiche() bypasses Picture/draw() and manipulates SDL::Surface/Rect/
// BltFast directly (clipped scrolling blit at screen edge).
// Deliberately left untouched - flagged in the audit (section C:
// "niejasne / wymaga decyzji") as needing a real design decision
// before any future Renderer extraction, not a mechanical move like
// the rest of the Sprite/Renderer step-1 migration.
void FondSnorkSas1::affiche(RenderQueue& rq)
{
	//Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						ys;
	Rect					r;
	int						largeur;
	int                     decalage = 0;

	surf = g_game_state.picture_banks().niveau()[1]->Surf();
	xs = g_game_state.picture_banks().niveau()[1]->xSize();
	ys = g_game_state.picture_banks().niveau()[1]->ySize();

	r.top		= 222 - etape;
	r.left		= 0;

	if (x + 53 > offset + 640)
		largeur = offset + 640 - x;
	else if (x < offset) {
		largeur = 53;
		r.left = offset - x;
		decalage = offset - x;
	} else
		largeur = 53;

	r.right		= largeur;
	r.bottom	= 222;

	backSurface->BltFast(x - offset + decalage, y , surf, &r, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
}


FondSnorkSas2::FondSnorkSas2()
{
	etape = 222;
}

void FondSnorkSas2::update()
{
	//si le sas 1 est verouillé...
	if ((FondSnorkSas1::etat) && (etape > 0)) {
		etape --;
	}


	if (etape % 8 == 0) {
		g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 8) / 8] = false;
		g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 16) / 8] = false;
		g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 24) / 8] = false;
		g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 32) / 8] = false;
		g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 40) / 8] = false;
		g_game_state.level().murs_opaques()[(y + etape) / 8][(x + 48) / 8] = false;
	}
}

void FondSnorkSas2::affiche(RenderQueue& rq)
{
	//Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						ys;
	Rect					r;
	int						largeur;
	int                     decalage = 0;

	surf = g_game_state.picture_banks().niveau()[1]->Surf();
	xs = g_game_state.picture_banks().niveau()[1]->xSize();
	ys = g_game_state.picture_banks().niveau()[1]->ySize();

	r.top		= 222 - etape;
	r.left		= 0;

	if (x + 53 > offset + 640)
		largeur = offset + 640 - x;
	else if (x < offset) {
		largeur = 53;
		r.left = offset - x;
		decalage = offset - x;
	} else
		largeur = 53;

	r.right		= largeur;
	r.bottom	= 222;

	backSurface->BltFast(x - offset + decalage, y , surf, &r, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
}
