/******************************************************************
*
*
*		--------------------
*		EnnemiSmurfPaysan.h
*		--------------------
*
*		Burn ! Burn ! Burn !
*
*
*		Mortimus / LOADED -   V 0.1 - 22 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfPaysan_
#define _EnnemiSmurfPaysan_

#define SMURF_PAYSAN_SPEED		4
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"
#include "game_state.h"
#include "globals.h"

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSmurf
//-----------------------------------------------------------------------------

class EnnemiSmurfPaysan : public Ennemi
{
public:
	int		tete_ss_etape ;
	int		tete_etape ;
	int		x_mort ;
	int		y_mort ;

	EnnemiSmurfPaysan();

	// Etap 3 (Sprite/Renderer separation, step 1): moved out-of-line to
	// ennemi_smurf_paysan.cpp. Unchanged otherwise.
	virtual void affiche();

	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
