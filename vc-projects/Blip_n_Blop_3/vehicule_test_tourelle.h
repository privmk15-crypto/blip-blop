
#ifndef _VehiculeTestTourelle_
#define _VehiculeTestTourelle_

#include "game_state.h"

class VehiculeTestTourelle : public Vehicule
{
public:

	int		lat;

	VehiculeTestTourelle() : lat(0)
	{
		pic = g_game_state.picture_banks().ennemis()[525];
	}

	virtual bool canFire()
	{
		return false;
	};

	virtual void updateNotUsed() {};

	virtual void updateUsed()
	{
		if (joueur->etat != ETAT_LOCKEDV || joueur->a_detruire) {
			joueur = NULL;
			return;
		}

		if (ctrl->gauche() && lat > -10) {
			lat--;

			if (lat <= -10 && dir > 0) {
				dir--;
				lat = 0;
			}
		}

		if (ctrl->droite() && lat < 10) {
			lat++;

			if (lat >= 10 && dir < 23) {
				dir++;
				lat = 0;
			}
		}

		pic = g_game_state.picture_banks().ennemis()[525 + dir];

		if (ctrl->saut()) {
			joueur->unlockVehicule();
			joueur = NULL;
		}
	}
};

#endif
