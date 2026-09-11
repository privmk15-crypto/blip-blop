/******************************************************************
 *
 *		----------------
 *		 CollisionSystem.cpp
 *		----------------
 *
 *		See collision_system.h for the extraction note. Body copied
 *		verbatim from the old Game::manageCollisions() (game.cpp),
 *		including its dead/shadowed `Tir* tir;`/`Ennemi* ennemi;`
 *		locals - neither touched, this is a pure move, not a cleanup.
 *
 ******************************************************************/

#include "collision_system.h"

#include "bonus.h"
#include "couille.h"
#include "enemy.h"
#include "game_state.h"
#include "tir.h"
#include "tir_bb_vache.h"

void CollisionSystem::Update(int wait_for_victory) {
    Tir* tir;
    Ennemi* ennemi;

    // Collisions TirsBB / Ennemis
    //
    for (Tir* tir : g_game_state.entities().list_tirs_bb()) {
        for (auto& ennemi : g_game_state.entities().list_ennemis()) {
            if (tir->collision(ennemi.get())) {
                ennemi->estTouche(tir);
            }
        }
    }

    // Collisions Vaches / Ennemis
    //
    for (auto& tir : g_game_state.entities().list_cow()) {
        for (auto& ennemi : g_game_state.entities().list_ennemis()) {
            if (tir->collision(ennemi.get())) {
                ennemi->estTouche(tir.get());
            }
        }
    }

    // Collisions Joueurs / Bonus
    //
    for (auto& bonus : g_game_state.entities().list_bonus()) {
        for (Couille* couille : g_game_state.entities().list_joueurs()) {
            if (bonus->collision(couille)) {
                bonus->estPris(couille);
            }
        }
    }

    if (wait_for_victory <= 0) {
        // Collisions Joueurs / Ennemis
        //
        for (auto& ennemi : g_game_state.entities().list_ennemis()) {
            for (Couille* joueur : g_game_state.entities().list_joueurs()) {
                if (ennemi->collision(joueur))
                    joueur->estTouche(ennemi->degats());
            }
        }

        // Collisions Joueurs / tirs ennemis
        //
        for (auto& tir : g_game_state.entities().list_tirs_ennemis()) {
            for (Couille* joueur : g_game_state.entities().list_joueurs()) {
                if (tir->collision(joueur)) {
                    joueur->estTouche(tir->degats());
                }
            }
        }
    }
}
