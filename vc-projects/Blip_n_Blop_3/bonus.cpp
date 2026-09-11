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
#include "render_queue.h"

void Bonus::affiche(RenderQueue& rq) {
    int base;

    y -= 15;
    Sprite::affiche(rq);

    if (local_phase)
        base = 0;
    else
        base = 4;

    int d = sini(8, phi);

    rq.Push(x - DIST_BITONIO - d, y - DIST_BITONIO - d, g_game_state.picture_banks().misc()[base + 3]);
    rq.Push(x + DIST_BITONIO + d, y - DIST_BITONIO - d, g_game_state.picture_banks().misc()[base + 2]);
    rq.Push(x + DIST_BITONIO + d, y + DIST_BITONIO + d, g_game_state.picture_banks().misc()[base]);
    rq.Push(x - DIST_BITONIO - d, y + DIST_BITONIO + d, g_game_state.picture_banks().misc()[base + 1]);

    y += 15;
}
