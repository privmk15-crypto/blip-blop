/******************************************************************
*
*
*		-----------------------
*		EnnemiSmurfPeon.h
*		-----------------------
*		Schtroumph de base.
*		Spécificité : Encaisse plus.
*
*		Mortimus / LOADED -   V 0.1 - 26 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfPeon_
#define _EnnemiSmurfPeon_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "ennemi_smurf.h"
#include "game_state.h"
#include "render_queue.h"

//-----------------------------------------------------------------------------
//		Définition de la classe
//-----------------------------------------------------------------------------

class EnnemiSmurfPeon : public EnnemiSmurf
{
public:

	EnnemiSmurfPeon()
	{
		pv = 125 ;
	}

	inline virtual void affiche(RenderQueue& rq)
	{
		EnnemiSmurf::affiche(rq) ;
		if ((etat != ETAT_MEURE && etat != ETAT_CARBONISE)
		        || (etat == ETAT_MEURE && etape <= 2)) {
			switch (dir) {
				case SENS_GAUCHE :
					rq.Push(x, y - 32, g_game_state.picture_banks().ennemis()[153]) ;
					break ;
				case SENS_DROITE :
					rq.Push(x, y - 32, g_game_state.picture_banks().ennemis()[154]) ;
					break ;
			}
		}
	}
};

#endif
