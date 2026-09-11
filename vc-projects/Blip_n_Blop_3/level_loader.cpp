/******************************************************************
 *
 *		----------------
 *		 LevelLoader.cpp
 *		----------------
 *
 *		See level_loader.h for the extraction note. Body copied
 *		verbatim from the old Game::chargeNiveau() (game.cpp), with
 *		xstart1/ystart1/xstart2/ystart2/vic_x/vic_flag1/vic_val1/
 *		vic_flag2/vic_val2 redirected from `this->` to `out.` and
 *		`this->rpg`/Precache() left calling through the passed-in
 *		RPGPlayer& - everything else (read order, sizes, error
 *		handling, debug<< logging) untouched.
 *
 ******************************************************************/

#include "level_loader.h"

#include <cstring>
#include <fstream>
#include <memory>

#include "ben_debug.h"
#include "config.h"
#include "dd_gfx.h"
#include "event_bonus.h"
#include "event_ennemi.h"
#include "event_fond_anime.h"
#include "event_gen_bonus.h"
#include "event_gen_ennemi.h"
#include "event_hold_fire.h"
#include "event_lock.h"
#include "event_meteo.h"
#include "event_mi_fond.h"
#include "event_music.h"
#include "event_premier_plan.h"
#include "event_rpg.h"
#include "event_scroll_speed.h"
#include "event_set_flag.h"
#include "event_son.h"
#include "event_texte.h"
#include "event_vehicule.h"
#include "fic_events.h"
#include "game_state.h"
#include "globals.h"
#include "precache.h"
#include "rpg_player.h"

bool LevelLoader::Load(const char* nom_niveau, RPGPlayer& rpg, Result& out) {
    char buffer[20];
    char buffer2[70];

    std::ifstream fic(nom_niveau, std::ios::binary);

    if (!fic.good()) {
        debug << "Game::chargeNiveau() -> Cannot load <" << nom_niveau << ">\n";
        return false;
    }

    debug
        << "---------------------------------------------------------------\n";
    debug << "Loading level <" << nom_niveau << ">\n";
    debug
        << "---------------------------------------------------------------\n";

    // GFX decors
    //
    fic.read(buffer, 20);
    strcpy(buffer2, "data/");
    strcat(buffer2, buffer);

    if (!g_game_state.picture_banks().decor().loadGFX(buffer2, DDSURF_SYSTEM)) {
        debug << "Game::chargeNiveau() -> Cannot load " << buffer2
              << " as background\n";
        return false;
    }

    debug << "Successfully loaded <" << buffer2 << "> as background\n";

    // GFX niveau (fonds animés & co)
    //
    fic.read(buffer, 20);
    if (strlen(buffer) != 0) {
        strcpy(buffer2, "data/");
        strcat(buffer2, buffer);

        if (!g_game_state.picture_banks().niveau().loadGFX(buffer2, mem_flag)) {
            debug << "Game::chargeNiveau() -> Cannot load " << buffer2
                  << " as level stuff\n";
            return false;
        }

        debug << "Successfully loaded <" << buffer2 << "> as level stuff\n";
    }

    // GFX ennemis
    //
    fic.read(buffer, 20);
    if (strlen(buffer) != 0) {
        strcpy(buffer2, "data/");
        strcat(buffer2, buffer);

        if (!g_game_state.picture_banks().ennemis().loadGFX(buffer2, mem_flag)) {
            debug << "Game::chargeNiveau() -> Cannot load " << buffer2
                  << " as ennemies\n";
            return false;
        }

        debug << "Successfully loaded <" << buffer2 << "> as ennemies\n";
    }

    // SBK ennemis
    //
    fic.read(buffer, 20);

    if (strlen(buffer) != 0) {
        strcpy(buffer2, "data/");
        strcat(buffer2, buffer);

        if (!g_game_state.sound_banks().sbk_niveau().loadSFX(buffer2)) {
            debug << "Game::chargeNiveau() -> Cannot load " << buffer2
                  << " as SBK\n";
            return false;
        }

        debug << "Successfully loaded <" << buffer2 << "> as SBK\n";
    }

    // Fichier MBK
    //
    fic.read(buffer, 20);
    if (strlen(buffer) != 0) {
        strcpy(buffer2, "data/");
        strcat(buffer2, buffer);
        strcpy(g_game_state.sound_banks().current_mbk(), buffer2);

        if (music_on) {
            if (!g_game_state.sound_banks().mbk_niveau().open(buffer2)) {
                debug << "Game::chargeNiveau() -> Cannot load " << buffer2
                      << " as MKB\n";
                return false;
            }
            debug << "Successfully loaded <" << buffer2 << "> as MBK\n";
        }
    } else
        strcpy(g_game_state.sound_banks().current_mbk(), "");

    // Fichier RPG itself
    //
    fic.read(buffer, 20);
    if (strlen(buffer) != 0) {
        strcpy(buffer2, "data/");
        strcat(buffer2, buffer);
        rpg.attachFile(buffer2);

        // Precache le fichier RPG
        //
        Precache(buffer2);

        debug << "Successfully loaded <" << buffer2 << "> as RPG file\n";
    }

    // GFX rpg
    //
    fic.read(buffer, 20);
    if (strlen(buffer) != 0) {
        strcpy(buffer2, "data/");
        strcat(buffer2, buffer);

        if (!g_game_state.picture_banks().rpg().loadGFX(buffer2, mem_flag)) {
            debug << "Game::chargeNiveau() -> Cannot load " << buffer2
                  << " as RPG GFX\n";
            return false;
        }

        debug << "Successfully loaded <" << buffer2 << "> as RPG GFX\n";
    }

    // Taille du niveau
    //
    int scr_level_size;
    fic.read(reinterpret_cast<char*>(&scr_level_size), sizeof(scr_level_size));
    g_game_state.level().set_scr_size(scr_level_size);
    g_game_state.level().set_size(scr_level_size * 640);

    // Numéros des écrans à afficher (comme des tiles)
    //
    int* num_decor = g_game_state.level().AllocNumDecor(scr_level_size);
    for (int i = 0; i < scr_level_size; i++)
        fic.read(reinterpret_cast<char*>(&num_decor[i]), sizeof(int));

    // Coordonnées de départ des joueurs
    //
    fic.read(reinterpret_cast<char*>(&out.xstart1), sizeof(out.xstart1));
    fic.read(reinterpret_cast<char*>(&out.ystart1), sizeof(out.ystart1));
    fic.read(reinterpret_cast<char*>(&out.xstart2), sizeof(out.xstart2));
    fic.read(reinterpret_cast<char*>(&out.ystart2), sizeof(out.ystart2));

    // Conditions de victoire
    //
    fic.read(reinterpret_cast<char*>(&out.vic_x), sizeof(out.vic_x));
    fic.read(reinterpret_cast<char*>(&out.vic_flag1), sizeof(out.vic_flag1));
    fic.read(reinterpret_cast<char*>(&out.vic_val1), sizeof(out.vic_val1));
    fic.read(reinterpret_cast<char*>(&out.vic_flag2), sizeof(out.vic_flag2));
    fic.read(reinterpret_cast<char*>(&out.vic_val2), sizeof(out.vic_val2));

    //
    // Plateformes
    //
    int** y_plat = g_game_state.level().AllocYPlat(g_game_state.level().size());

    for (int i = 0; i < NB_MAX_PLAT; i++) {
        fic.read(reinterpret_cast<char*>(y_plat[i]),
                 (g_game_state.level().size()) * sizeof(int));
    }

    //
    // Murs opaques
    //
    int level_size_8 = g_game_state.level().size() / 8;
    bool** murs_opaques = g_game_state.level().AllocMursOpaques(level_size_8);

    for (int i = 0; i < 60; i++) {
        fic.read(reinterpret_cast<char*>(murs_opaques[i]),
                 (level_size_8) * sizeof(bool));
    }

    //
    // Murs sanglants
    //
    bool** murs_sanglants = g_game_state.level().AllocMursSanglants(level_size_8);

    for (int i = 0; i < 60; i++) {
        fic.read(reinterpret_cast<char*>(murs_sanglants[i]),
                 (level_size_8) * sizeof(bool));
    }

    //
    // Charge les évenements
    //
    FICEVENT ficevent;
    int nb_events;

    fic.read(reinterpret_cast<char*>(&nb_events), sizeof(nb_events));

    for (int i = 0; i < nb_events; i++) {
        fic.read(reinterpret_cast<char*>(&ficevent), sizeof(ficevent));

        switch (ficevent.event_id) {
            case EVENTID_ENNEMI: {
                auto event_ennemi = std::make_unique<EventEnnemi>();

                event_ennemi->x_activation = ficevent.x_activation;
                event_ennemi->id_ennemi = ficevent.id;
                event_ennemi->x = ficevent.x;
                event_ennemi->y = ficevent.y;
                event_ennemi->sens = ficevent.sens;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_ennemi));
                break;
            }

            case EVENTID_ENNEMI_GENERATOR: {
                auto event_gennemi = std::make_unique<EventGenEnnemi>();

                event_gennemi->x_activation = ficevent.x_activation;
                event_gennemi->id_ennemi = ficevent.id;
                event_gennemi->x = ficevent.x;
                event_gennemi->y = ficevent.y;
                event_gennemi->sens = ficevent.sens;
                event_gennemi->capacite = ficevent.capacite;
                event_gennemi->periode = ficevent.periode;
                event_gennemi->tmp = ficevent.tmp;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_gennemi));
                break;
            }

            case EVENTID_LOCK: {
                auto event_lock = std::make_unique<EventLock>();

                event_lock->x_activation = ficevent.x_activation;
                event_lock->cond = ficevent.cond;
                event_lock->flag = ficevent.flag;
                event_lock->val = ficevent.val;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_lock));
                break;
            }

            case EVENTID_FORCE_SCROLL: {
                auto event_scroll_speed = std::make_unique<EventScrollSpeed>();

                event_scroll_speed->x_activation = ficevent.x_activation;
                event_scroll_speed->speed = ficevent.speed;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_scroll_speed));
                break;
            }

            case EVENTID_FLAG: {
                auto event_set_flag = std::make_unique<EventSetFlag>();

                event_set_flag->x_activation = ficevent.x_activation;
                event_set_flag->flag = ficevent.flag;
                event_set_flag->val = ficevent.val;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_set_flag));
                break;
            }

            case EVENTID_HOLD_FIRE: {
                auto event_hold_fire = std::make_unique<EventHoldFire>();

                event_hold_fire->x_activation = ficevent.x_activation;
                event_hold_fire->flag = ficevent.flag;
                event_hold_fire->val = ficevent.val;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_hold_fire));
                break;
            }

            case EVENTID_BONUS_GENERATOR: {
                auto event_gen_bonus = std::make_unique<EventGenBonus>();

                event_gen_bonus->x_activation = ficevent.x_activation;
                event_gen_bonus->type = ficevent.id;
                event_gen_bonus->periode = ficevent.periode;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_gen_bonus));
                break;
            }

            case EVENTID_TEXT: {
                auto event_texte = std::make_unique<EventTexte>();

                event_texte->x_activation = ficevent.x_activation;
                event_texte->ntxt = ficevent.n_txt;
                event_texte->cond = ficevent.cond;
                event_texte->flag = ficevent.flag;
                event_texte->val = ficevent.val;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_texte));
                break;
            }

            case EVENTID_FOND_ANIME: {
                auto event_fond_anime = std::make_unique<EventFondAnime>();

                event_fond_anime->x_activation = ficevent.x_activation;
                event_fond_anime->id_fond = ficevent.id;
                event_fond_anime->x = ficevent.x;
                event_fond_anime->y = ficevent.y;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_fond_anime));
                break;
            }

            case EVENTID_MIFOND: {
                auto event_mi_fond = std::make_unique<EventMiFond>();

                event_mi_fond->x_activation = ficevent.x_activation;
                event_mi_fond->id = ficevent.id;
                event_mi_fond->x = ficevent.x;
                event_mi_fond->y = ficevent.y;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_mi_fond));
                break;
            }

            case EVENTID_PREMIER_PLAN: {
                auto event_pplan = std::make_unique<EventPremierPlan>();

                event_pplan->id_fond = ficevent.id;
                event_pplan->x_activation = ficevent.x_activation;
                event_pplan->x = ficevent.x;
                event_pplan->y = ficevent.y;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_pplan));
                break;
            }

            case EVENTID_RPG: {
                auto event_rpg = std::make_unique<EventRPG>();

                event_rpg->x_activation = ficevent.x_activation;
                event_rpg->num = ficevent.id;
                event_rpg->cond = ficevent.cond;
                event_rpg->flag = ficevent.flag;
                event_rpg->val = ficevent.val;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_rpg));
                break;
            }

            case EVENTID_MUSIC: {
                auto event_music = std::make_unique<EventMusic>();

                event_music->x_activation = ficevent.x_activation;
                event_music->id = ficevent.id;
                event_music->play = ficevent.play;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_music));
                break;
            }

            case EVENTID_METEO: {
                auto event_meteo = std::make_unique<EventMeteo>();

                event_meteo->x_activation = ficevent.x_activation;
                event_meteo->intensite = ficevent.intensite;
                event_meteo->type = ficevent.id;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_meteo));
                break;
            }

            case EVENTID_BONUS: {
                auto event_bonus = std::make_unique<EventBonus>();
                event_bonus->x_activation = ficevent.x_activation;
                event_bonus->type = ficevent.id;
                event_bonus->x = ficevent.x;
                event_bonus->y = ficevent.y;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_bonus));
                break;
            }

            case EVENTID_TURRET: {
                auto event_vehicule = std::make_unique<EventVehicule>();
                event_vehicule->x_activation = ficevent.x_activation;
                event_vehicule->id_vehicule = ficevent.id;
                event_vehicule->x = ficevent.x;
                event_vehicule->y = ficevent.y;
                event_vehicule->dir = ficevent.dir;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_vehicule));
                break;
            }

            case EVENTID_SON: {
                auto event_son = std::make_unique<EventSon>();
                event_son->x_activation = ficevent.x_activation;
                event_son->nsnd = ficevent.id;

                g_game_state.entities().list_event_endormis().push_back(std::move(event_son));
                break;
            }
        }
    }

    debug << "Successfully loaded all level files\n";

    return true;
}
