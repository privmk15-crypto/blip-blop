/******************************************************************
 *
 *		----------------
 *		 PlayerManager.h
 *		----------------
 *
 *		Owns the two Couille* player slots that used to be Game's own
 *		player1/player2 members (game.h before this migration):
 *		created (`new Blip()`/`new Blop()`) and destroyed (`delete`)
 *		by Game::jouePartie(), read everywhere else in game.cpp for
 *		HUD, victory/defeat, scoring, and menu logic.
 *
 *		Scope of this step: only the two Couille* slots move here -
 *		not xstart1/ystart1/xstart2/ystart2 (level-file start
 *		coordinates) or ctrlP1_/ctrlP2_ (input controllers), which
 *		stay Game members, since they're per-slot *configuration*
 *		Game hands to a player at creation time, not part of what
 *		"the roster of active players" means. This is a first step
 *		toward N players, not a complete one: player1()/player2()
 *		return Couille*& (not Couille* by value) so every one of the
 *		~120 existing call sites in game.cpp keeps working completely
 *		unchanged in shape (`player1 = new Blip();`,
 *		`if (player1 != NULL) ...`, `delete player1; player1 =
 *		NULL;`) via a simple `player1` -> `player_manager_.player1()`
 *		rename; only player(int)/count() below are new, generic,
 *		index-based accessors nothing calls yet, added so future code
 *		has a path to iterate players generically instead of matching
 *		on the two hardcoded names.
 *
 *		Owned by Game (game.h) as `player_manager_`, not by GameState:
 *		like CollisionSystem/EventSystem/LevelLoader, this is
 *		Game-session lifecycle (who's currently playing), not
 *		gameplay world state - GameState already separately exposes a
 *		read-only, non-owning view of the same two pointers via
 *		g_game_state.entities().list_joueurs() (unchanged by this
 *		migration).
 *
 ******************************************************************/

#pragma once

class Couille;

class PlayerManager {
   public:
    static constexpr int kMaxPlayers = 2;

    // Named accessors - preserve every existing call site's shape
    // unchanged (assignment, comparison, deletion) via reference return.
    Couille*& player1() { return players_[0]; }
    Couille*& player2() { return players_[1]; }

    // Index/count-based accessors - not used anywhere yet, but let future
    // code (e.g. HUD/collision/victory logic) iterate players generically
    // instead of hardcoding player1/player2, without requiring every call
    // site to change today.
    int count() const { return kMaxPlayers; }
    Couille*& player(int index) { return players_[index]; }
    Couille* player(int index) const { return players_[index]; }

   private:
    Couille* players_[kMaxPlayers] = {nullptr, nullptr};
};
