#pragma once

#include <iomanip>
#include <sstream>

#include "couille.h"
#include "game_state.h"
#include "globals.h"

class HUD {
   public:
    enum class Location : int { Left, Right };
    enum class Color { Blue, Orange };

    void Draw(Couille* player,
              Location location,
              Color color,
              bool bonus_stage) {
        DrawHealth(player->pv, location);
        DrawScore(player->getScore(), location, color);
        if (bonus_stage) {
            DrawBonusStage(location);
        } else {
            DrawLives(player->nb_life, location);
        }
        DrawWeapon(player->id_arme, location);

        // FIXME: The drawer clearly should be agnostic of what are the base
        // weapons with unlimited ammo.
        if (player->id_arme == ID_M16) {
            DrawAmmo(-1, false, location);
        } else {
            DrawAmmo(player->ammo, player->tire, location);
        }
        DrawCowBomb(player->nb_cow_bomb, location);
    }

   private:
    void DrawCowBomb(int nb, Location location) {
        if (location == Location::Left) {
            for (int i = 0, dxt = 0; i < nb; i++, dxt += 23)
                g_game_state.picture_banks().misc()[49]->BlitTo(backSurface, 90 + dxt, 65);
        } else {
            // Etap 4 (Full HD fix): was a bare 520 (640 - 120 margin from
            // the old right edge) - kept the same margin past SCREEN_W.
            for (int i = 0, dxt = 0; i < nb; i++, dxt += 23)
                g_game_state.picture_banks().misc()[49]->BlitTo(backSurface, SCREEN_W - 120 - dxt, 65);
        }
    }

    void DrawAmmo(int ammo, bool firing, Location location) {
        // Etap 4 (Full HD fix): 505 was 640 - 135 - the same margin as
        // the Left case's 135, mirrored - kept mirrored against SCREEN_W.
        int x = location == Location::Left ? 135 : SCREEN_W - 135;
        if (ammo == -1) {
            g_game_state.font_bank().ammo().printC(backSurface, x, 43, "*");
            return;
        }

        std::string ammo_str = std::to_string(ammo);
        if (firing) {
            g_game_state.font_bank().ammo_used().printC(backSurface, x, 43, ammo_str.c_str());
        } else {
            g_game_state.font_bank().ammo().printC(backSurface, x, 43, ammo_str.c_str());
        }
    }

    void DrawWeapon(int weapon, Location location) {
        Picture* pic;

        switch (weapon) {
            case ID_M16:
                pic = g_game_state.picture_banks().misc()[14];
                break;
            case ID_PM:
                pic = g_game_state.picture_banks().misc()[8];
                break;
            case ID_LF:
                pic = g_game_state.picture_banks().misc()[11];
                break;
            case ID_FUSIL:
                pic = g_game_state.picture_banks().misc()[9];
                break;
            case ID_LASER:
                pic = g_game_state.picture_banks().misc()[10];
                break;
        }

        // Etap 4 (Full HD fix): 510 was 640 - 130 margin from the old
        // right edge - kept the same margin past SCREEN_W.
        int x = (location == Location::Left) ? 135 : SCREEN_W - 130;
        pic->BlitTo(backSurface, x, 50);
    }

    void DrawBonusStage(Location location) {
        if (location == Location::Left) {
            g_game_state.font_bank().rpg().print(backSurface, 4, 5, "Bonus");
            g_game_state.font_bank().rpg().print(backSurface, 4, 20, "Stage");
        } else {
            // Etap 4 (Full HD fix): 635 was 640 - 5 margin from the old
            // right edge - kept the same margin past SCREEN_W.
            g_game_state.font_bank().rpg().printR(backSurface, SCREEN_W - 5, 5, "Bonus");
            g_game_state.font_bank().rpg().printR(backSurface, SCREEN_W - 5, 20, "Stage");
        }
    }

    void DrawLives(int lives, Location location) {
        if (location == Location::Left) {
            g_game_state.font_bank().cool().print(backSurface, 5, 5, std::to_string(lives).c_str());
        } else {
            // Etap 4 (Full HD fix): same 640-5 margin as DrawBonusStage.
            g_game_state.font_bank().cool().printR(backSurface, SCREEN_W - 5, 5, std::to_string(lives).c_str());
        }
    }

    void DrawScore(int score, Location location, Color color) {
        std::ostringstream oss;
        oss << std::setw(7) << std::setfill('0') << score;
        std::string s = oss.str();

        // Etap 4 (Full HD fix): 450 was 640 - 190 margin from the old
        // right edge - kept the same margin past SCREEN_W.
        int x = (location == Location::Left) ? 100 : SCREEN_W - 190;
        if (color == Color::Blue) {
            g_game_state.font_bank().score_blip().print(backSurface, x, 20, s.c_str());
        } else {
            g_game_state.font_bank().score_blop().print(backSurface, x, 20, s.c_str());
        }
    }

    static void DrawHealth(int health, Location location) {
        static const int x_health[] = {3, 0, 13, 44, 31};
        static const int y_health[] = {0, 21, 48, 21, 0};
        // Etap 4 (Full HD fix): 560 was 640 - 80 margin from the old
        // right edge - kept the same margin past SCREEN_W.
        static const int pos[2][2] = {{20, 20}, {SCREEN_W - 80, 20}};

        int x = pos[int(location)][0];
        int y = pos[int(location)][1];

        for (int i = 0; i < health; i++) {
            g_game_state.picture_banks().bb()[201 - i]->BlitTo(
                backSurface, x + x_health[i], y + y_health[i]);
        }

        for (int i = health; i < 5; i++) {
            g_game_state.picture_banks().bb()[196 - i]->BlitTo(
                backSurface, x + x_health[i], y + y_health[i]);
        }
    }
};
