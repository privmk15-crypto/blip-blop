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

#include "event.h"
#include "game_state.h"

void EventSystem::Update() {
    Event* event;

    // Les évenements de la liste "endormie" sont mis dans la liste "en attente"
    // quand ils sont sur le point d'être activés
    //
    // FIXME: These reverse iterators are WEIRD. Why are the events coming
    // in reverse order? This feels so backward.
    for (auto it = g_game_state.entities().list_event_endormis().rbegin();
         it != g_game_state.entities().list_event_endormis().rend();
         ++it) {
        auto& event = *it;
        if (!event->aReveiller()) {
            break;
        }
        g_game_state.entities().list_event().push_back(std::move(event));
    }

    g_game_state.entities().list_event_endormis().erase(
        std::remove_if(g_game_state.entities().list_event_endormis().begin(),
                       g_game_state.entities().list_event_endormis().end(),
                       [](auto& ev) { return !ev.get(); }),
        g_game_state.entities().list_event_endormis().end());

    // Si les évenements "en attente" doivent être activés, on les active
    //
    for (auto& event : g_game_state.entities().list_event()) {
        if (event->aActiver()) {
            event->doEvent();
            event.reset(nullptr);
        }
    }

    g_game_state.entities().list_event().erase(
        std::remove_if(g_game_state.entities().list_event().begin(),
                        g_game_state.entities().list_event().end(),
                        [](auto& ev) { return !ev.get(); }),
        g_game_state.entities().list_event().end());
}
