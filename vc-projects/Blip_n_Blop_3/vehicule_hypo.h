
#ifndef _VehiculeHypo_
#define _VehiculeHypo_

#include "vehicule.h"
#include "game_state.h"

class VehiculeHypo : public Vehicule
{
public:

	bool	has_been_used;

	VehiculeHypo() : has_been_used(false)
	{
		pic = g_game_state.picture_banks().ennemis()[255];
	}

	virtual bool canFire()
	{
		return true;
	};

	virtual bool canChangeDir()
	{
		return false;
	};

	virtual void updateUsed();
	virtual void updateNotUsed();
	virtual void affiche();
};

#endif
