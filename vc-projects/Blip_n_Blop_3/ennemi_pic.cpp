#include "ennemi_pic.h"
#include "game_state.h"
#include "globals.h"


EnnemiPic::EnnemiPic(): y_origine(0)
{
	pv = 1;
	pic = g_game_state.picture_banks().ennemis()[168];
}

void EnnemiPic::update()
{
	if ((g_game_state.game_flags()[0] == 3) || (g_game_state.game_flags()[0] == 2)) {
		if (-104 > y_origine) {
			//les pics sont sortis inutiles de les faire monter plus
		} else if (-96 > y_origine) {
			y -= 1;
			y_origine -= 1;
		} else if (-86 > y_origine) {
			y -= 2;
			y_origine -= 2;
		} else if (-66 > y_origine) {
			y -= 4;
			y_origine -= 4;
		} else if (-46 > y_origine) {
			y -= 6;
			y_origine -= 6;
		} else if (-26 > y_origine) {
			y -= 8;
			y_origine -= 8;
		} else if (0 >= y_origine) {
			y -= 10;
			y_origine -= 10;
		}
		colFromPic();
	} else if (g_game_state.game_flags()[0] >= 5) {
		if (-104 > y_origine) {
			y += 10;
			y_origine += 10;
		} else if (-96 > y_origine) {
			y += 8;
			y_origine += 8;
		} else if (-86 > y_origine) {
			y += 6;
			y_origine += 6;
		} else if (-66 > y_origine) {
			y += 4;
			y_origine += 4;
		} else if (-46 > y_origine) {
			y += 3;
			y_origine += 3;
		} else if (-26 > y_origine) {
			y += 2;
			y_origine += 2;
		} else if (0 >= y_origine) {
			y += 1;
			y_origine += 1;
		} else {
			//les pics sont rentrés donc on peut les detruires....
			for (int i = 28; i <= 55; i++)
				g_game_state.level().murs_opaques()[i][108] = false;

			a_detruire = true;
		}
		colFromPic();
	}
}



// Etap 3 (Sprite/Renderer separation) audit finding: bypasses
// Picture/draw() and manipulates SDL::Surface/Rect/BltFast directly
// (clipped blit). Deliberately left untouched - flagged in the audit
// (section C: "niejasne / wymaga decyzji") as needing a real design
// decision before any future Renderer extraction, not a mechanical
// move like the rest of the Sprite/Renderer step-1 migration.
void EnnemiPic::affiche()
{
	//Sprite::affiche();
	SDL::Surface *	surf;
	int						xs;
	int						ys;
	Rect					r;
	//int						largeur;


	surf = g_game_state.picture_banks().ennemis()[168]->Surf();
	xs = g_game_state.picture_banks().ennemis()[168]->xSize();
	ys = g_game_state.picture_banks().ennemis()[168]->ySize();

	r.top		= 0 ;
	r.left		= 0;


	//largeur = 39;

	r.right		= 39;
	r.bottom	= -y_origine;

	backSurface->BltFast(x - offset , y , surf, &r, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
}

void EnnemiPic::colFromPic()
{
	Sprite::colFromPic();

	x2 += 25;
	x1 += 25;
}

void EnnemiPic::estTouche(Tir * tir)
{
}
