/******************************************************************
 *
 *		--------------------
 *		 PlayerToggles.h
 *		--------------------
 *
 *		Owns three shared (not per-player) gameplay toggles: okBonus,
 *		cowBombOn, okLanceFlame (globals.h/.cpp before this
 *		migration).
 *
 *		These were flagged in the Stage 2 Phase 1 analysis as a
 *		"shared global toggle" smell in a two-player game - closer
 *		inspection during this migration shows they're not actually
 *		a per-player bug: okBonus is a per-frame cache of "is ANY
 *		player bonus-eligible right now" (OR of each Couille's own
 *		per-player okBonus() method - see Couille::okBonus(), a
 *		different, unrelated symbol despite the name collision);
 *		cowBombOn and okLanceFlame are genuinely session/level-wide
 *		flags (cow bomb unlock progress for the playthrough, and
 *		whether the current level allows the flamethrower). All
 *		three are intentionally shared, not accidentally so - but
 *		per instruction this migration preserves them exactly as
 *		shared state regardless, without attempting to split them
 *		per-player.
 *
 *		Owned by GameState (game_state.h) as
 *		g_game_state.player_toggles() because enemy.cpp and
 *		couille.cpp read these with no reachable Game/GameState
 *		instance, even though every write originates inside Game's
 *		own methods.
 *
 ******************************************************************/

#pragma once

class PlayerToggles {
   public:
    void set_ok_bonus(bool v) { ok_bonus_ = v; }
    void set_cow_bomb_on(bool v) { cow_bomb_on_ = v; }
    void set_ok_lance_flame(bool v) { ok_lance_flame_ = v; }

    bool ok_bonus() const { return ok_bonus_; }
    bool cow_bomb_on() const { return cow_bomb_on_; }
    bool ok_lance_flame() const { return ok_lance_flame_; }

   private:
    bool ok_bonus_ = false;
    bool cow_bomb_on_ = false;
    bool ok_lance_flame_ = false;
};

// Owned by GameState (game_state.h) as g_game_state.player_toggles() - no
// standalone global instance here anymore.
