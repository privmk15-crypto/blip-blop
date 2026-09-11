/******************************************************************
 *
 *		----------------
 *		 EventSystem.h
 *		----------------
 *
 *		Owns the per-frame Event dispatch loop that used to live in
 *		Game::updateEvents() (game.cpp before this migration): wakes
 *		"endormis" (sleeping) events whose aReveiller() says they're
 *		ready, moves them into the pending queue, then runs and
 *		clears any pending event whose aActiver() returns true.
 *
 *		Storage (list_event/list_event_endormis) already lives in
 *		EntityManager (g_game_state.entities()) since the earlier
 *		Stage 2 EntityManager migration - this class only moves the
 *		loop that drives them out of Game, unchanged in behavior
 *		(including the FIXME'd reverse iteration below, preserved
 *		exactly as found).
 *
 *		Stateless (no members) - a plain function would do just as
 *		well, but this matches the class-per-system shape used
 *		elsewhere (CollisionSystem, HUD, UpdateRegulator) rather than
 *		adding a free function to an already-crowded namespace.
 *
 ******************************************************************/

#pragma once

class EventSystem {
   public:
    // Equivalent to the old Game::updateEvents().
    void Update();
};
