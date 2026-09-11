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
    // Used to reverse-iterate and break on the first not-yet-ready event
    // (the FIXME below is the original author's own doubt about that -
    // "why are the events coming in reverse order? This feels so
    // backward"). That relied on list_event_endormis() being pre-sorted
    // descending by x_activation, which is nowhere enforced or
    // documented - it just happens to hold for an unmodified level file.
    // Confirmed this breaks for real: shifting some events' x_activation
    // (to fix Full HD's spawn-pop-in-early problem) without perfectly
    // preserving relative order caused a not-yet-ready event to block
    // the early-break, silently starving every event "behind" it in the
    // list of ever waking up. Now checks every sleeping event every
    // frame instead - list_event_endormis() is at most a few hundred
    // entries even on a full level, so the cost is negligible, and it's
    // correct regardless of what order the data happens to be in.
    // FIXME (original, left as historical record - no longer relevant
    // now that order isn't assumed): These reverse iterators are WEIRD.
    for (auto it = g_game_state.entities().list_event_endormis().begin();
         it != g_game_state.entities().list_event_endormis().end();) {
        auto& event = *it;
        if (event->aReveiller()) {
            g_game_state.entities().list_event().push_back(std::move(event));
            it = g_game_state.entities().list_event_endormis().erase(it);
        } else {
            ++it;
        }
    }

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
