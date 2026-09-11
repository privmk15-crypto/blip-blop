/******************************************************************
 *
 *		----------------
 *		 GameFlags.h
 *		----------------
 *
 *		Owns the old global game_flag[11] array (globals.h/.cpp before
 *		this migration): a
 *		general-purpose per-level flag array, independently read and
 *		written by the Event system (EventSetFlag and friends), many
 *		EnnemiXxx classes (some via the FLAG_* macros in globals.h -
 *		FLAG_USER1-3/FLAG_BULLES/FLAG_BONUS/FLAG_TIMER/FLAG_GEN_OFF/
 *		FLAG_NB_KILL/FLAG_NB_ENN/FLAG_NB_GEN - others via raw numeric
 *		indices that are level-script-specific and have no symbolic
 *		name), Game::updateLock()/updateVictoryAndDefeat(), and
 *		several FondXxx decor classes (elevators, falling crates,
 *		switches).
 *
 *		Deliberately kept as a flat indexable array (operator[]),
 *		not split into 11 named fields: the FLAG_* macros already
 *		name the slots that have a stable meaning, and several
 *		indices are reused ad hoc per level script with meanings that
 *		only make sense in that level's own Event graph - splitting
 *		those into named fields would invent structure the original
 *		code never had. Same "migrate the ownership, not the
 *		semantics" approach as PlayerToggles/HoldFire.
 *
 *		Owned by GameState (game_state.h) as g_game_state.game_flags()
 *		as part of the Stage 2 ownership migration.
 *
 ******************************************************************/

#pragma once

class GameFlags {
   public:
    static constexpr int kCount = 11;

    int& operator[](int i) { return flags_[i]; }
    const int& operator[](int i) const { return flags_[i]; }

   private:
    int flags_[kCount] = {};
};

// Owned by GameState (game_state.h) as g_game_state.game_flags() - no
// standalone global array here anymore.
