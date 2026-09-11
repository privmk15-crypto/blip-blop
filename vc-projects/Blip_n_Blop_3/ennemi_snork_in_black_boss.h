/******************************************************************
*
*
*		-----------------------------
*		    EnnemiSnorkInBlackBoss.h
*		-----------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 23 Avril 2001
*
*
*
******************************************************************/

#ifndef _EnnemiSnorkInBlackBoss_
#define _EnnemiSnorkInBlackBoss_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

//#define SNORK_IN_BLACK_MAX_TIR		6
// Renamed from the generic `tolerance` (Etap 3 build fix): collided
// with an identifier of the same name pulled in transitively once this
// translation unit gained a globals.h include (SDL2/libstdc++ system
// header, not anything in this codebase - verified via a full-repo
// grep finding no other definition of `tolerance` anywhere). Every
// sibling constant in this file family is already prefixed/uppercase;
// this one was the sole lowercase, unprefixed outlier.
#define SNORK_BOSS_TOLERANCE		5

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSnorkyInBlackBoss
//-----------------------------------------------------------------------------

class EnnemiSnorkInBlackBoss : public Ennemi
{
private:
	int nb_tir;
	int position;
	int type_attack;
	int dx;
	bool attack;

	int x_shark;
	int y_shark;
	bool shark;
	bool saut;

public:

	EnnemiSnorkInBlackBoss();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onTire();
	virtual void affiche(RenderQueue& rq);


	virtual void estTouche(Tir * tir);
};

#endif