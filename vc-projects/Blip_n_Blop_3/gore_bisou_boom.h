
#ifndef _GoreBisouBoom_
#define _GoreBisouBoom_

#include "sprite.h"
#include "game_state.h"
#include "globals.h"

class GorePiedBisouBoom : public Sprite
{
public:
	virtual void update()
	{
		tombe();

		if (etape < 5) {
			ss_etape += 1;
			ss_etape %= 8;

			if (ss_etape == 0)
				etape += 1;

			if (dir == SENS_DROITE)
				pic = g_game_state.picture_banks().ennemis()[190 + etape];
			else
				pic = g_game_state.picture_banks().ennemis()[196 + etape];
		}


		if ((plat(x, y) != 0 && etape >= 5) || mur_opaque(x, y)) {
			grave(x, y, pic);
			a_detruire = true;
			g_game_state.sound_banks().sbk_misc().play(6 + (rand() % 2));
		} else {
			if (dir == SENS_DROITE)
				x -= 2;
			else
				x += 2;
		}


		updateADetruire();
	};
};

class GoreTeteBisouBoom : public Sprite
{
public:
	virtual void update()
	{
		tombe();

		if (etape < 5) {
			ss_etape += 1;
			ss_etape %= 8;

			if (ss_etape == 0)
				etape += 1;

			if (dir == SENS_DROITE)
				pic = g_game_state.picture_banks().ennemis()[202 + etape];
			else
				pic = g_game_state.picture_banks().ennemis()[208 + etape];
		}


		if ((plat(x, y) != 0 && etape >= 5) || mur_opaque(x, y)) {
			grave(x, y, pic);
			a_detruire = true;
			g_game_state.sound_banks().sbk_misc().play(6 + (rand() % 2));
		} else {
			if (dir == SENS_DROITE)
				x += 2;
			else
				x -= 2;
		}

		updateADetruire();
	};
};

class GoreBideBisouBoom : public Sprite
{
public:
	virtual void update()
	{
		tombe();

		if (etape < 5) {
			ss_etape += 1;
			ss_etape %= 8;

			if (ss_etape == 0)
				etape += 1;

			if (dir == SENS_DROITE)
				pic = g_game_state.picture_banks().ennemis()[214 + etape];
			else
				pic = g_game_state.picture_banks().ennemis()[220 + etape];
		}


		if ((plat(x, y) != 0 && etape >= 5) || mur_opaque(x, y)) {
			grave(x, y, pic);
			g_game_state.sound_banks().sbk_misc().play(6 + (rand() % 2));
			a_detruire = true;
		} else {
			if (dir == SENS_DROITE)
				x += 1;
			else
				x -= 1;
		}

		updateADetruire();
	};
};

#endif
