/******************************************************************
*
*
*		-----------------------
*		    NomPasAJour.h
*		-----------------------
*
*
*
*		Prosper / LOADED -   dates à la con ? =)
*
*
*
******************************************************************/

#ifndef _TirHadoken_
#define _TirHadoken_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"
#include "game_state.h"


#define DELAY_ACCELERATION 20

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirHadoken : public Tir
{
public:

	/*

	TODO:Is this method used? where?

	int TirSnorkybase();

	*/

	virtual int degats() const
	{
		return 1;
	};

	virtual int enflame() const
	{
		return 0;
	};

	virtual void setDir(int d)
	{
		dir = d;
	};

	virtual void update()
	{
		static const int SPEED = 8;

		ss_etape += 1;
		ss_etape %= 2;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 3;
		}

		if (etape == 2) {
			pic = NULL;
		} else {
			if (dir == SENS_DROITE) {
				x += SPEED;
				pic = g_game_state.picture_banks().ennemis()[219 + etape];
			} else {
				x -= SPEED;
				pic = g_game_state.picture_banks().ennemis()[221 + etape];
			}
		}

		if (mur_opaque(x, y))
			a_detruire = true;

		updateADetruire();
		colFromPic();
	};

};

#endif
