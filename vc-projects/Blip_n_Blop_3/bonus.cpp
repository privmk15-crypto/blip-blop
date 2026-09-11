/******************************************************************
 *
 *
 *		----------------
 *		    Bonus.cpp
 *		----------------
 *
 *		Etap 3 (Sprite/Renderer separation, step 1): Bonus::affiche()
 *		moved out-of-line from bonus.h, unchanged. See bonus.h for the
 *		note.
 *
 ******************************************************************/

#include "bonus.h"

#include "ben_maths.h"
#include "game_state.h"
#include "globals.h"

void Bonus::affiche() {
    int base;

    y -= 15;
    Sprite::affiche();

    if (local_phase)
        base = 0;
    else
        base = 4;

    int d = sini(8, phi);

    draw(x - DIST_BITONIO - d, y - DIST_BITONIO - d, g_game_state.picture_banks().misc()[base + 3]);
    draw(x + DIST_BITONIO + d, y - DIST_BITONIO - d, g_game_state.picture_banks().misc()[base + 2]);
    draw(x + DIST_BITONIO + d, y + DIST_BITONIO + d, g_game_state.picture_banks().misc()[base]);
    draw(x - DIST_BITONIO - d, y + DIST_BITONIO + d, g_game_state.picture_banks().misc()[base + 1]);

    y += 15;
}
