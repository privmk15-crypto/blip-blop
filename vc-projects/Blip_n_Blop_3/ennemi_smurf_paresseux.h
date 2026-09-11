/******************************************************************
*
*
*		-----------------------
*		EnnemiSmurfParesseux.h
*		-----------------------
*		Schtroumph de base.
*		Spécificité : Saute un peu moins haut.
*
*		Mortimus / LOADED -   V 0.1 - 26 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfParesseux_
#define _EnnemiSmurfParesseux_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "ennemi_smurf.h"
#include "game_state.h"
#include "render_queue.h"

//-----------------------------------------------------------------------------
//		Définition de la classe
//-----------------------------------------------------------------------------

class EnnemiSmurfParesseux : public EnnemiSmurf
{
public:

	EnnemiSmurfParesseux()
	{
		dy_saut = -4 ;
	}

	inline virtual void affiche(RenderQueue& rq)
	{
		EnnemiSmurf::affiche(rq) ;
		/*
				if(etat != ETAT_MEURE && etat != ETAT_CARBONISE)
				{
					switch(dir)
					{
						case SENS_GAUCHE :
						draw(x-8,y-35,g_game_state.picture_banks().ennemis()[152]) ;
						break ;
						case SENS_DROITE :
						draw(x+8,y-35,g_game_state.picture_banks().ennemis()[152]) ;
						break ;
					}
				}
		*/
	}
};

#endif
