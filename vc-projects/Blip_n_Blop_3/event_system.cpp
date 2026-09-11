/******************************************************************
 *
 *		----------------
 *		 EventSystem.cpp
 *		----------------
 *
 *		See event_system.h for the extraction note. Body copied
 *		verbatim from the old Game::updateEvents() (game.cpp),
 *		including its dead/shadowed `Event* event;` local and the
 *		FIXME comment about the reverse iteration - neither touched,
 *		this is a pure move, not a cleanup.
 *
 ******************************************************************/

#include "event_system.h"

#include <algorithm>

#include "ben_debug.h"
#include "event.h"
#include "game_state.h"

void EventSystem::Update() {
    Event* event;

    // TEMPORARY DIAGNOSTIC LOGGING - to find why reported enemy spawns
    // stop happening under a data/code change we can't reproduce
    // locally. Writes to BlipBlop.log next to the exe. Safe to revert
    // once we have real data from a run - changes no behavior, only
    // adds debug<< calls.
    static bool logged_start = false;
    if (!logged_start) {
        debug << "[SPAWN-DEBUG] EventSystem::Update() first call - "
                 "list_event_endormis()=" << g_game_state.entities().list_event_endormis().size()
              << " list_event()=" << g_game_state.entities().list_event().size() << "\n";
        logged_start = true;
    }

    // Les évenements de la liste "endormie" sont mis dans la liste "en attente"
    // quand ils sont sur le point d'être activés
    //
    // FIXME: These reverse iterators are WEIRD. Why are the events coming
    // in reverse order? This feels so backward.
    int woke_this_frame = 0;
    for (auto it = g_game_state.entities().list_event_endormis().rbegin();
         it != g_game_state.entities().list_event_endormis().rend();
         ++it) {
        auto& event = *it;
        if (!event->aReveiller()) {
            break;
        }
        woke_this_frame++;
        g_game_state.entities().list_event().push_back(std::move(event));
    }

    if (woke_this_frame > 0) {
        debug << "[SPAWN-DEBUG] offset=" << offset << " woke " << woke_this_frame
              << " event(s), sleeping_before=" << g_game_state.entities().list_event_endormis().size()
              << "\n";
    }

    g_game_state.entities().list_event_endormis().erase(
        std::remove_if(g_game_state.entities().list_event_endormis().begin(),
                       g_game_state.entities().list_event_endormis().end(),
                       [](auto& ev) { return !ev.get(); }),
        g_game_state.entities().list_event_endormis().end());

    // Si les évenements "en attente" doivent être activés, on les active
    //
    int activated_this_frame = 0;
    for (auto& event : g_game_state.entities().list_event()) {
        if (event->aActiver()) {
            event->doEvent();
            activated_this_frame++;
            event.reset(nullptr);
        }
    }

    if (activated_this_frame > 0) {
        debug << "[SPAWN-DEBUG] offset=" << offset << " activated " << activated_this_frame
              << " event(s) via doEvent(). list_ennemis()=" << g_game_state.entities().list_ennemis().size()
              << " list_gen_ennemis()=" << g_game_state.entities().list_gen_ennemis().size()
              << " list_event_endormis() remaining=" << g_game_state.entities().list_event_endormis().size()
              << "\n";
    }

    g_game_state.entities().list_event().erase(
        std::remove_if(g_game_state.entities().list_event().begin(),
                        g_game_state.entities().list_event().end(),
                        [](auto& ev) { return !ev.get(); }),
        g_game_state.entities().list_event().end());
}
