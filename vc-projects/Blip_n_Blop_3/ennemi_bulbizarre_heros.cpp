/******************************************************************
*
*
*		-----------------------------
*		  EnnemiBulbizarreHeros.cpp
*		-----------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 14 Janvier 2001
*
*
*
******************************************************************/


#include "ennemi_bulbizarre_heros.h"
#include "game_state.h"
#include "globals.h"


EnnemiBulbizarreHeros::EnnemiBulbizarreHeros(): dorkeball(2)
{
	pv = 1500;
	dy = -8;
	dx = -2;
}

void EnnemiBulbizarreHeros::update()
{
	if (dorkeball == 2) {
		x += dx;
		tombe();
		int yp;
		if ((dy > 0) && (yp = plat(x, y + dy)) != 0) {
			etat = ETAT_NORMAL;
			dy = 0;
			y = yp;
			etape = 0;
			ss_etape = 0;
			dorkeball = 1;
			return;
		} else {
			ss_etape ++;
			ss_etape %= 5;
			if (ss_etape == 0) {
				etape ++;
				etape %= 4;
			}
			pic = g_game_state.picture_banks().ennemis()[272 + etape];
		}
	} else if (dorkeball == 1) {
		ss_etape ++;
		ss_etape %= 8;
		if (ss_etape == 0) {
			etape ++;
			if (etape > 3) {
				dorkeball = 0;
				etape = 0;
				ss_etape = 0;
			} else {
				pic = g_game_state.picture_banks().ennemis()[384 + etape];
			}
		}

	} else {
		if (blood > 0)
			blood -= 1;

		switch (etat) {
			case ETAT_NORMAL:
			case ETAT_AVANCE:
				onAvance();
				break;


			case ETAT_MEURE:
			case ETAT_CARBONISE:
				onMeure();
				break;
		}

		updateADetruire();
	}
}

void EnnemiBulbizarreHeros::onAvance()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	// Marche
	//
	if (x - 1 < xmin || mur_opaque(x - 1, y))
		dir = SENS_DROITE;
	else if (x + 1 > offset + 640 || mur_opaque(x + 1, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(2);
		pic = g_game_state.picture_banks().ennemis()[310 + etape];
	} else {
		marche(-2);
		pic = g_game_state.picture_banks().ennemis()[312 + etape];
	}
	colFromPic();
}

void EnnemiBulbizarreHeros::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0 && etape < 8)
		etape += 1;

	if (etape >= 8) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != g_game_state.level().y_plat()[4][x])
			grave(x, y, pic);

		g_game_state.game_flags()[1] --;
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = g_game_state.picture_banks().ennemis()[322 + etape];
		else
			pic = g_game_state.picture_banks().ennemis()[314 + etape];
	}
}


void EnnemiBulbizarreHeros::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	if (dorkeball == 0) {
		Ennemi::estTouche(tir);
		gicle(tir, dx_giclure, dy_giclure);
	}
}
