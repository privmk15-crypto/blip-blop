/******************************************************************
*
*
*		---------------------------
*		    FondPokeInterupteur.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"
#include "game_state.h"
#include "fond_poke_interupteur.h"
#include "enemy.h"
#include "texte_cool.h"

const int anim_interupteur_on[] = {84 , 85, 86, 84};
const int anim_interupteur_off[] = {81 , 82, 83, 82};

FondPokeInterupteur::FondPokeInterupteur(): etat(false), wait_msg(false), ascenc_msg(false), bravo(false)
{
}

void FondPokeInterupteur::update()
{
	ss_etape ++;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape ++;
		etape %= 4;
	}

	if (etat) {
		pic = pbk_niveau[anim_interupteur_on[etape]];
	} else {
		if (tete_turc != NULL) {
			if ((tete_turc->x > x - 10) && (tete_turc->x < x + 33) && (tete_turc->y > y - 10) && (tete_turc->y < y + 51)) {
				g_game_state.game_flags()[2] ++;
				etat = true;
				sbk_niveau.play(2);
			}
		}
		pic = pbk_niveau[anim_interupteur_off[etape]];
	}


	if (x < offset - 100)
		a_detruire = true;

	if (g_game_state.game_flags()[0] == 0) {
		if (wait_msg || g_game_state.game_flags()[2] == 0) {
			g_game_state.game_flags()[7] = 1;
		} else {
			g_game_state.game_flags()[7] = 0;
		}
	}

	if (!wait_msg && g_game_state.game_flags()[2] == 0 && g_game_state.game_flags()[6] <= 80) {
		wait_msg = true;
		TexteCool * txt = new TexteCool();
		txt->ntxt = 104;
		g_game_state.entities().list_txt_cool().emplace_back(txt);
	}

	if (!ascenc_msg && wait_msg && g_game_state.game_flags()[2] == 1) {
		ascenc_msg = true;
		TexteCool * txt = new TexteCool();
		txt->ntxt = 105;
		g_game_state.entities().list_txt_cool().emplace_back(txt);
		txt = new TexteCool();
		txt->ntxt = 106;
		g_game_state.entities().list_txt_cool().emplace_back(txt);
	}

	if (!bravo && ascenc_msg && g_game_state.game_flags()[0] == 1) {
		bravo = true;
		TexteCool * txt = new TexteCool();
		txt->ntxt = 107;
		g_game_state.entities().list_txt_cool().emplace_back(txt);
	}
};
