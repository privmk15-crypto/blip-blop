
#include "vehicule_hypo.h"
#include "globals.h"

void VehiculeHypo::affiche(RenderQueue& rq)
{
	Sprite::affiche(rq);

	if (joueur != NULL)
		joueur->affiche(rq);
}

void VehiculeHypo::updateUsed()
{
	static const int SPEED = 3;

	has_been_used = true;
	can_be_used = false;

	if (ctrl->gauche() && x > offset + 40 && !mur_opaque(x - SPEED, y)) {
		x -= SPEED;
	}

	if (ctrl->droite() && x < offset + SCREEN_W - 40 && !mur_opaque(x + SPEED, y)) {
		x += SPEED;
	}

	if (ctrl->haut() && y > 40 && !mur_opaque(x, y - SPEED)) {
		y -= SPEED;
	}

	if (ctrl->bas() && y < 440 && !mur_opaque(x, y + SPEED)) {
		y += SPEED;
	}

	joueur->dir = BBDIR_DROITE;
	joueur->dir_arme = BBDIR_DROITE;
	joueur->x = x;
	joueur->y = y;

	if (ctrl->saut()) {
		joueur->unlockVehicule();
		joueur = NULL;
	}
}


void VehiculeHypo::updateNotUsed()
{
	if (has_been_used)
		x += 10;
}
