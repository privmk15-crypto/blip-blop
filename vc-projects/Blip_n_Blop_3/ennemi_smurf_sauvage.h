/******************************************************************
*
*
*		--------------------
*		EnnemiSmurfSauvage.h
*		--------------------
*
*		Le schtroumph brujah
*
*
*		Mortimus / LOADED -   V 0.1 - 23 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfSauvage_
#define _EnnemiSmurfSauvage_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"
#include "game_state.h"
#include "globals.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define DIAGONALE_GAUCHE		0
#define DIAGONALE_BAS_GAUCHE	1
#define BAS_GAUCHE				2
#define BAS_DROITE				3
#define DIAGONALE_BAS_DROITE	4
#define DIAGONALE_DROITE		5

#define ETAT_ATTENDS			100
#define ETAT_MONTE				102

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSmurfSauvage
//-----------------------------------------------------------------------------

class EnnemiSmurfSauvage : public Ennemi
{
public:
	int shoot_direction ; // direction dans laquelle on pointe l'arme
	int hauteur ;
	int pente ;		  // coefficient directeur de la droite
	// passant par tete_turc et le smurfSauvage
	int num_pic ;
	int etape_shoot ;
	int nb_shoot ;

	static int	wait_shoot;
	static int	etape_wait;

	bool first_loop;
	bool mort ;
	bool position;

	int ss_etape_angle;
	int angle;
	bool sensAngle;

	bool shooting;

	Sprite *	cible;

	EnnemiSmurfSauvage();

	// Etap 3 (Sprite/Renderer separation, step 1): moved out-of-line to
	// ennemi_smurf_sauvage.cpp. Unchanged otherwise.
	virtual void affiche();

	virtual void update();
	virtual void onTombe() ;
	virtual void onTire() ;
	virtual void onMeure();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
};

#endif
