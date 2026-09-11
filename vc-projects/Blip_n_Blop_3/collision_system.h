/******************************************************************
 *
 *		----------------
 *		 CollisionSystem.h
 *		----------------
 *
 *		Owns the 4 collision passes that used to live in
 *		Game::manageCollisions() (game.cpp before this migration):
 *		tirs-bb/ennemis, cow-bombs/ennemis, joueurs/bonus, and (only
 *		while no victory is pending) joueurs/ennemis and
 *		joueurs/tirs-ennemis.
 *
 *		wait_for_victory is passed in rather than read from GameState
 *		because it's a Game-owned timer (game.h), not gameplay world
 *		state - this class only reads entity lists
 *		(g_game_state.entities()), it doesn't need its own state.
 *
 ******************************************************************/

#pragma once

class CollisionSystem {
   public:
    // Equivalent to the old Game::manageCollisions(). wait_for_victory
    // mirrors Game's own member of the same name: while it's > 0,
    // player-damaging collisions (joueurs/ennemis, joueurs/tirs
    // ennemis) are skipped, exactly as before.
    void Update(int wait_for_victory);
};
