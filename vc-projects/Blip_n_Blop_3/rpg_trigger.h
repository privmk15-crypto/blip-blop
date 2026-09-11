/******************************************************************
 *
 *		----------------
 *		 RpgTrigger.h
 *		----------------
 *
 *		Owns rpg_to_play (globals.h/.cpp before this migration):
 *		which RPG cutscene phase (-1 = none) EventRPG has queued up
 *		for Game::updateRPG() to play.
 *
 *		Owned by GameState (game_state.h) as g_game_state.rpg_trigger()
 *		because EventRPG::doEvent() has no reachable Game/GameState
 *		instance to call through.
 *
 ******************************************************************/

#pragma once

class RpgTrigger {
   public:
    void Set(int num) { num_ = num; }
    void Clear() { num_ = -1; }
    int num() const { return num_; }

   private:
    int num_ = -1;  // -1: none pending, matches the original's initializer
};

// Owned by GameState (game_state.h) as g_game_state.rpg_trigger() - no
// standalone global instance here anymore.
