
#include "ennemi_smurf_cigogne.h"
#include "ben_maths.h"
#include "game_state.h"

EnnemiSmurfCigogne::EnnemiSmurfCigogne() {
    pic = g_game_state.picture_banks().ennemis()[355];
    noCol();
    first = true;
}

void EnnemiSmurfCigogne::update() {
    if (first) {
        base_y = y;
        x -= 100;
        base_x = x;
        first = false;
    }

    if (g_game_state.game_flags()[1] < 5) return;

    x += 4;

    y = base_y + sini(100, ((x - base_x) / 4) % 360);

    if (x > offset + 750 && g_game_state.game_flags()[0] < 3) {
        g_game_state.game_flags()[0] = 3;
    }
}
